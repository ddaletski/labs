// 3_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "3_1.h"

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
	LoadStringW(hInstance, IDC_MY3_1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3_1));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3_1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY3_1);
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


void drawPerson(HDC hdc, RECT rect) {

	int height = rect.bottom - rect.top;
	int width = rect.right - rect.left;
	int l = rect.left, t = rect.top;

	int headTop = 0, headBottom = height * 0.2, headLeft = width * 0.4, headRight = width * 0.6;
	int bodyTop = headBottom, bodyBottom = height * 0.6,
		bodyLeft = width * 0.3, bodyRight = width * 0.7;

	double legWidth = 0.35;
	int llegLeft = bodyLeft, llegRight = bodyLeft * (1 - legWidth) + bodyRight * legWidth;
	int rlegLeft = bodyLeft * legWidth + bodyRight * (1 - legWidth), rlegRight = bodyRight;


	double armWidth = 0.25;
	double armLenght = 0.75;
	int larmLeft = bodyLeft - armWidth * (bodyRight - bodyLeft);
	int rarmRight = bodyRight + armWidth * (bodyRight - bodyLeft);
	int armBottom = armLenght * bodyBottom + (1 - armLenght) * bodyTop;


	Ellipse(hdc, l + headLeft, t + headTop, l + headRight, t + headBottom);
	Rectangle(hdc, l + bodyLeft, t + bodyTop, l + bodyRight, t + bodyBottom);

	Rectangle(hdc, l + llegLeft, t + bodyBottom, l + llegRight, t + height);
	Rectangle(hdc, l + rlegLeft, t + bodyBottom, l + rlegRight, t + height);

	Rectangle(hdc, l + larmLeft, t + bodyTop, l + bodyLeft, t + armBottom);
	Rectangle(hdc, l + bodyRight, t + bodyTop, l + rarmRight, t + armBottom);
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
	static double speed = 7;
	static double acceleration = 0.2;

	static RECT personRect;
	static RECT clientRect;
	static double gap;

	switch (message)
	{
	case WM_CREATE:
	{
		gap = 0;
		SetTimer(hWnd, NULL, 1, NULL);
	}
	break;
	case WM_TIMER:
	{
		gap = gap >= (clientRect.right - clientRect.left) ? personRect.left - personRect.right : gap + speed;
		speed += acceleration;
		if (speed > 30 || speed <= 2)
			acceleration *= -1;
		InvalidateRect(hWnd, &clientRect, true);
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
		GetClientRect(hWnd, &clientRect);
		static int personWidth = 0.2 * (clientRect.right - clientRect.left);
		int vcenter = 0.25 * clientRect.bottom + 0.75 * clientRect.top + 0.1 * gap;

		personRect.right = clientRect.right - gap;
		personRect.left = personRect.right - personWidth;
		personRect.top = max(clientRect.top, vcenter - 0.7 * (personRect.right - personRect.left));
		personRect.bottom = min(clientRect.bottom, vcenter + 0.7 * (personRect.right - personRect.left));

		drawPerson(hdc, personRect);

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
