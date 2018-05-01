// 4_1.cpp : Defines the entry point for the application.
 // 

#define UNICODE

#include "stdafx.h"
#include "4_1.h"
#include <windowsx.h>

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
	LoadStringW(hInstance, IDC_MY4_1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY4_1));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY4_1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY4_1);
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

RECT updateRect(int centerX, int centerY, int size) {
	RECT rect;
	rect.left = centerX - size / 2;
	rect.right = centerX + size / 2;
	rect.top = centerY - size / 2;
	rect.bottom = centerY + size / 2;
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
	static int currentSize;
	static int maxSize;
	static int minSize;
	static int centerX;
	static int centerY;
	static int windowExtraWidth;
	static int windowExtraHeight;

	static RECT clientRect;
	static RECT currentRect;

	switch (message)
	{
	case WM_CREATE:
	{
		GetClientRect(hWnd, &clientRect);
		centerX = 0.5 * (clientRect.left + clientRect.right);
		centerY = 0.5 * (clientRect.top + clientRect.bottom);
		currentSize = min(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		maxSize = currentSize;
		minSize = max(maxSize / 16, 8);

		currentRect = updateRect(centerX, centerY, currentSize);

		RECT windowRect;
		GetWindowRect(hWnd, &windowRect);
		windowExtraHeight = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);
		windowExtraWidth = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		if (x >= currentRect.left && x <= currentRect.right && y <= currentRect.bottom && y >= currentRect.top) {
			currentSize = min(maxSize, currentSize * 1.1);
		}
		currentRect = updateRect(centerX, centerY, currentSize);
		InvalidateRect(hWnd, &clientRect, true);
	}
	break;

	case WM_RBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		if (x >= currentRect.left && x <= currentRect.right && y <= currentRect.bottom && y >= currentRect.top) {
			currentSize = max(currentSize / 1.1, minSize);
		}

		currentRect = updateRect(centerX, centerY, currentSize);
		InvalidateRect(hWnd, &clientRect, true);
	}
	break;

	case WM_SIZE:
	{
		GetClientRect(hWnd, &clientRect);
		centerX = 0.5 * (clientRect.left + clientRect.right);
		centerY = 0.5 * (clientRect.top + clientRect.bottom);
		maxSize = min(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		minSize = max(maxSize / 16, 8);

		currentRect = updateRect(centerX, centerY, currentSize);
	}
	break;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = currentSize + windowExtraWidth;
		lpMMI->ptMinTrackSize.y = currentSize + windowExtraHeight;
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		Rectangle(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
		RECT textRect(currentRect);
		textRect.right--;
		textRect.bottom--;

		HFONT font;
		font = CreateFont(currentSize / 10, 0, 0, 0, 0, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, 0, TEXT("Arial"));
		SelectObject(hdc, font);
		DrawText(hdc, TEXT("Далецкий"), 8, &textRect, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
		DeleteObject(font);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
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
