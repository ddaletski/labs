// 3_5.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "3_5.h"
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
typedef std::pair<double, double> Point2d;


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY35, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY35));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY35));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY35);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


POINT Point(int x, int y) {
	POINT p;
	p.x = x;
	p.y = y;

	return p;
}

std::vector<Point2d> functionPoints(double(*f)(double), double from, double to, int count) {
	std::vector<Point2d> points;

	double step = (to - from) / count;

	double x = from;
	for (int i = 0; i < count; ++i, x+=step) {
		points.push_back({ x, f(x) });
	}

	return points;
}


std::tuple<std::vector<POINT>, double, double, double, double>
	scalePointsToRect(RECT rect, const std::vector<Point2d>& points) 
{
	std::vector<POINT> result;

	double xmin = std::min_element(points.begin(), points.end(), [](const Point2d& p1, const Point2d& p2) { return p1.first < p2.first; })->first;
	double ymin = std::min_element(points.begin(), points.end(), [](const Point2d& p1, const Point2d& p2) { return p1.second < p2.second; })->second;
	double xmax = std::min_element(points.begin(), points.end(), [](const Point2d& p1, const Point2d& p2) { return p1.first > p2.first; })->first;
	double ymax = std::min_element(points.begin(), points.end(), [](const Point2d& p1, const Point2d& p2) { return p1.second > p2.second; })->second;

	double xscale = (rect.right - rect.left) / (xmax - xmin);
	double xshift = rect.right - xmax * xscale;
	double yscale = (rect.bottom - rect.top) / (ymax - ymin);
	double yshift = rect.bottom - ymax * yscale;


	for (auto& point : points) {
		POINT p = Point(
			xshift + point.first * xscale,
			rect.bottom - (yshift + point.second * yscale)
		);
		result.push_back(p);
	}

	return { result, xscale, xshift, yscale, yshift };
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int steps = 200;
	const int radius = 50;

	static auto points = functionPoints([](double x) { return sin(x); }, -2 * M_PI, 2 * M_PI, steps);
	static std::vector<POINT> scaledPoints;
	static RECT clientRect;

	static int idx = 0;
	static int speed = 1;
	static double angle = 0;
	static double angleStep = speed * 4 * M_PI / steps;

	static HPEN dottedPen = CreatePen(PS_DOT, 1, RGB(200, 200, 200));

    switch (message)
    {
	case WM_CREATE:
	{
		GetClientRect(hWnd, &clientRect);
		scaledPoints = std::get<0>(scalePointsToRect(clientRect, points));
		SetTimer(hWnd, NULL, 20, NULL);
	}
	break;
	case WM_TIMER:
	{
		idx += speed;
		angle = fmod(angle + angleStep, 2*M_PI);

		if (speed > 0 && idx >= scaledPoints.size() - 1) {
			speed = -speed;
			angleStep = -angleStep;
			idx = scaledPoints.size() - 1;
		} else if (speed < 0 && idx <= 0) {
			speed = -speed;
			angleStep = -angleStep;
			idx = 0;
		}

		InvalidateRect(hWnd, NULL, true);
	} 
	break;
	case WM_SIZE:
	{
		GetClientRect(hWnd, &clientRect);
		scaledPoints = std::get<0>(scalePointsToRect(clientRect, points));
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

			auto defaultPen = SelectObject(hdc, dottedPen);
			Polyline(hdc, scaledPoints.data(), scaledPoints.size());
			SelectObject(hdc, defaultPen);

			POINT center = scaledPoints[idx];
			Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);

			POINT surfacePoint = Point(center.x + radius * cos(angle), center.y + radius * sin(angle));
			POINT linePoints[2] = { center, surfacePoint };
			Polyline(hdc, linePoints, 2);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DeleteObject(dottedPen);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
