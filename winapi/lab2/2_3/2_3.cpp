// 2_3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "2_3.h"
#include <string>
#include <vector>
#include <memory>

typedef std::vector<HBRUSH> Brushes;
#define CIRCLES_COUNT 10

void initBrushes(int circlesCount, Brushes& similarBrushes, Brushes& contrastBrushes) {
	similarBrushes.clear();
	contrastBrushes.clear();

	int colorStart = 0;
	int colorStop = 255;
	int colorStep = (colorStop - colorStart) / circlesCount;

	std::vector<int> colors{ rand() % 256, rand() % 256, rand() % 256 };
	int randomColorIndex = rand() % 3;
	int randomColorIndex2 = rand() % 3;

	for (int i = 0; i < circlesCount; ++i) {
		colors[randomColorIndex] = colorStart + colorStep * i;
		colors[randomColorIndex2] = colorStart + colorStep * i;
		HBRUSH brush{ CreateSolidBrush(RGB(colors[0], colors[1], colors[2])) };
		similarBrushes.push_back(brush);
		HBRUSH brush2{ CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)) };
		contrastBrushes.push_back(brush2);
	}
}

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
    LoadStringW(hInstance, IDC_MY23, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY23));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY23));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY23);
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
	static int mode = 1;
	static RECT clientRect;

	static int circlesCount = CIRCLES_COUNT;
	static int width;
	static int height;
	static int minDimension;
	static int center;
	static int maxRadius;
	static int minRadius;
	static float radiusStep;

	static Brushes similarBrushes;
	static Brushes contrastBrushes;
	static HBRUSH defaultBrush = GetSysColorBrush(0);
	static HPEN transparentPen;
	static HPEN opaquePen;

    switch (message)
    {
	case WM_CREATE:
	{
		initBrushes(circlesCount, similarBrushes, contrastBrushes);
		transparentPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
		opaquePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	}
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
	case WM_LBUTTONDOWN:
	{
		mode = 1 - mode;
		initBrushes(circlesCount, similarBrushes, contrastBrushes);
		InvalidateRect(hWnd, &clientRect, true);
	}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...

			GetClientRect(hWnd, &clientRect);
			width = clientRect.right - clientRect.left;
			height = clientRect.bottom - clientRect.top;
			minDimension = min(width, height);
			center = minDimension / 2;
			maxRadius = minDimension / 2;
			minRadius = 1;
			radiusStep = float(maxRadius - minRadius) / circlesCount;


			for (int i = 0; i < circlesCount; ++i) {
				int radius = maxRadius - i * radiusStep;
				int left = center - radius;
				int right = center + radius;
				int top = left, bottom = right;

				HBRUSH brush;
				HPEN pen;
				if (mode == 0) {
					brush = &(*similarBrushes[i]);
					pen = transparentPen;
				} else {
					brush = &(*contrastBrushes[i]);
					pen = opaquePen;
				}

				SelectObject(hdc, brush);
				SelectObject(hdc, pen);
				Ellipse(hdc, left, top, right, bottom);
			}

			SelectObject(hdc, defaultBrush);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		while (contrastBrushes.size()) {
			DeleteObject(contrastBrushes.back());
			contrastBrushes.pop_back();
		}

		while (similarBrushes.size()) {
			DeleteObject(similarBrushes.back());
			similarBrushes.pop_back();
		}

		DeleteObject(transparentPen);
		DeleteObject(opaquePen);

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
