// 2_4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "2_4.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

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
    LoadStringW(hInstance, IDC_MY24, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY24));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY24));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY24);
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

void Line(HDC hdc, double x1, double y1, double x2, double y2){
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	return;
}

void Triangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3) {
	POINT points[3];
	points[0].x = x1;
	points[0].y = y1;
	points[1].x = x2;
	points[1].y = y2;
	points[2].x = x3;
	points[2].y = y3;

	Polygon(hdc, points, 3);
}

void Quadrangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	POINT points[4];
	points[0].x = x1;
	points[0].y = y1;
	points[1].x = x2;
	points[1].y = y2;
	points[2].x = x3;
	points[2].y = y3;
	points[3].x = x4;
	points[3].y = y4;

	Polygon(hdc, points, 4);
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
	static int unit;
	static std::vector<HBRUSH> brushes;

    switch (message)
    {
	case WM_CREATE:
		brushes = {
			CreateSolidBrush(RGB(255, 255, 0)),
			CreateSolidBrush(RGB(0, 255, 0)),
			CreateSolidBrush(RGB(255, 0, 255)),
			CreateSolidBrush(RGB(255, 125, 0)),
			CreateSolidBrush(RGB(0, 200, 255)),
			CreateSolidBrush(RGB(255, 68, 0)),
			CreateSolidBrush(RGB(0, 0, 255))
		};
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
			SetGraphicsMode(hdc, GM_ADVANCED);
			RECT clientRect;
			GetClientRect(hWnd, &clientRect);

			int width = clientRect.right - clientRect.left;
			int height = clientRect.bottom - clientRect.top;

			unit = min(width, height) / 7;

			double rot = M_PI / 4;
			XFORM xfm = { 0.0f };
			xfm.eM11 = (float)cos(rot);
			xfm.eM12 = (float)sin(rot);
			xfm.eM21 = (float)-sin(rot);
			xfm.eM22 = (float)cos(rot);
			xfm.eDx = 4 * unit;
			xfm.eDy = 0.25 * unit;

			double sq2 = sqrt(2);

			SetWorldTransform(hdc, &xfm);
			SelectObject(hdc, brushes[5]);
			Rectangle(hdc, 0, 0, unit, unit); // 6

			SelectObject(hdc, brushes[0]);
			Triangle(hdc,
				unit / 2, unit,
				2.5*unit, unit,
				2.5*unit, 3 * unit
			); // 1

			SelectObject(hdc, brushes[2]);
			Quadrangle(hdc, 
				2.5 * unit, 3 * unit, 
				2.5 * unit, 4*unit, 
				1.5 * unit, 3 * unit, 
				1.5 * unit, 2 * unit
			); // 3

			SelectObject(hdc, brushes[1]);
			Triangle(hdc, 
				2.5 * unit, 2 * unit, 
				2.5 * unit, 4 * unit, 
				4.5 * unit, 4 * unit
			); // 2

			SelectObject(hdc, brushes[3]);
			Triangle(hdc, 
				2.5 * unit, 4 * unit, 
				2.5 * unit, (4 + sq2) * unit, 
				(2.5 + sq2) *unit, 4 * unit
			); // 4

			SelectObject(hdc, brushes[4]);
			Triangle(hdc, 
				(2.5 + sq2) * unit, 4 * unit, 
				(2.5 + 2*sq2) * unit, 4 * unit, 
				(2.5 + 1.5*sq2) * unit, (4 + sq2/2) * unit
			); // 5

			SelectObject(hdc, brushes[6]);
			Triangle(hdc, 
				((2.5 + sq2/4) * unit), (4 + 0.75*sq2) * unit,
				((2.5 + sq2/4) * unit), (4 + 1.75*sq2) * unit,
				((2.5 - sq2/4) * unit), (4 + 1.25 * sq2) * unit
			); // 7

			XFORM xfm_def;

			xfm_def.eM11 = 1,
			xfm_def.eM12 = 0,
			xfm_def.eM21 = 0,
			xfm_def.eM22 = 1,
			xfm_def.eDx = 0,
			xfm_def.eDy = 0,
			SetWorldTransform(hdc, &xfm_def);

			DrawText(hdc, TEXT("Вариант 1, Далецкий Д.А."), -1, &clientRect, DT_SINGLELINE | DT_TOP | DT_CENTER);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		for (auto brush : brushes)
			DeleteObject(brush);

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
