// 3_3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "3_3.h"
#include <windowsx.h>
#include <vector>

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
	LoadStringW(hInstance, IDC_MY3_3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3_3));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3_3));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY3_3);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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


void drawRect(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void drawCircle(HDC hdc, RECT rect) {
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void drawTriangle(HDC hdc, RECT rect) {
	POINT points[3];
	points[0].x = rect.left;
	points[0].y = rect.top;
	points[1].x = rect.right;
	points[1].y = rect.top;
	points[2].x = 0.5 * (rect.left + rect.right);
	points[2].y = rect.bottom;
	Polygon(hdc, points, 3);
}


bool inRect(int x, int y, RECT rect) {
	if (x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom) {
		return true;
	}
	return false;
}

RECT centeredRect(int hcenter, int vcenter, int width, int height) {
	RECT rect;
	rect.top = vcenter - height / 2;
	rect.bottom = vcenter + height / 2;
	rect.left = hcenter - width / 2;
	rect.right = hcenter + width / 2;
	return rect;
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
	static double sizeCoeffs[3] = { 1, 1, 1 };
	static bool isActive[3] = { false, false, false };
	static RECT rects[3];
	static double scaling = 0.95;
	static std::vector<HBRUSH> brushes;

	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, NULL, 300, NULL);
		brushes = std::vector<HBRUSH> {
			CreateSolidBrush(RGB(200, 50, 50)),
			CreateSolidBrush(RGB(50, 200, 50)),
			CreateSolidBrush(RGB(50, 50, 200))
		};
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
	case WM_LBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		for (int i = 0; i < 3; ++i) {
			if (inRect(x, y, rects[i])) {
				isActive[i] = true;
			}
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		for (int i = 0; i < 3; ++i) {
			if (inRect(x, y, rects[i])) {
				isActive[i] = false;
			}
		}
	}
	break;
	case WM_TIMER:
	{
		bool update = false;
		for (int i = 0; i < 3; ++i) {
			if (isActive[i]) {
				sizeCoeffs[i] = sizeCoeffs[i] == 1 ? scaling : 1;
				update = true;
			}
		}
		if (update) {
			InvalidateRect(hWnd, NULL, true);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		int width = clientRect.right - clientRect.left;
		int height = clientRect.bottom - clientRect.top;
		int itemWidth = width / 3;
		int itemHeight = height / 3;

		int hcenter = clientRect.left + 20 + width / 6;
		int vcenter = clientRect.top + 20 + height / 6;
		rects[0] = centeredRect(hcenter, vcenter, itemWidth * sizeCoeffs[0], itemHeight * sizeCoeffs[0]);

		hcenter = clientRect.right - 20 - width / 6;
		rects[1] = centeredRect(hcenter, vcenter, itemWidth * sizeCoeffs[1], itemHeight * sizeCoeffs[1]);

		hcenter = (clientRect.left + clientRect.right) / 2;
		vcenter = clientRect.bottom - 20 - height / 6;
		rects[2] = centeredRect(hcenter, vcenter, itemWidth * sizeCoeffs[2], itemHeight * sizeCoeffs[2]);

		SelectObject(hdc, brushes[0]);
		drawRect(hdc, rects[0]);

		SelectObject(hdc, brushes[1]);
		drawTriangle(hdc, rects[1]);

		SelectObject(hdc, brushes[2]);
		drawCircle(hdc, rects[2]);


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		for (auto b : brushes) {
			DeleteObject(b);
		}
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
