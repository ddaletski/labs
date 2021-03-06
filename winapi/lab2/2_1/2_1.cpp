// 2_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "2_1.h"
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <vector>
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>




HPEN hVioletPen;
HBRUSH hPinkBrush;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCWSTR szClassName = TEXT("WinAPI");
LPCWSTR szTitle = TEXT("Lab 2 - 1");

HINSTANCE globalInstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmadLine, int nCmdShow)
{
	MSG msg;
	if (!hPrevInstance)
	{
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wc.hCursor = LoadCursor(NULL, IDC_HELP);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 9);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	globalInstance = hInstance;
	HWND hWnd;
	hWnd = CreateWindow(
		szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)    return (FALSE);
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
	return (TRUE);
}

void Line(HDC, double, double, double , double);

std::vector<RECT> splitArea(HDC& hdc, RECT& areaRect, int rows, int cols) {
	int totalHeight = areaRect.bottom - areaRect.top;
	int totalWidth = areaRect.right - areaRect.left;

	int partHeight = totalHeight / rows;
	int partWidth = totalWidth / cols;

	std::vector<RECT> parts;
	for (int i = 0; i < rows; ++i) {
		RECT rect;
		rect.top = areaRect.top + i * partHeight;
		rect.bottom = areaRect.top + (i + 1) * partHeight;

		Line(hdc, areaRect.left, rect.top, areaRect.right, rect.top);
		Line(hdc, areaRect.left, rect.bottom, areaRect.right, rect.bottom);

		for (int j = 0; j < cols; ++j) {
			rect.left = areaRect.left + j * partWidth;
			rect.right = areaRect.left + (j + 1) * partWidth;

			if (i == 0) {
				Line(hdc, rect.left, areaRect.top, rect.left, areaRect.bottom);
				Line(hdc, rect.right, areaRect.top, rect.right, areaRect.bottom);
			}

			parts.push_back(rect);
		}
	}


	return parts;
}


void drawRect(HDC& hdc, RECT& roi) {
	Rectangle(hdc, roi.left + 10, roi.top + 10, roi.right - 10, roi.bottom - 10);
	TextOut(hdc, roi.left + 5, roi.top + 1, TEXT("Прямоугольник"), 13);
}


void drawSquare(HDC& hdc, RECT& roi) {
	int horCenter = (roi.left + roi.right) / 2;
	int verCenter = (roi.top + roi.bottom) / 2;

	int totalHeight = roi.bottom - roi.top;
	int totalWidth = roi.right - roi.left;

	int side = 0.45 * min(totalHeight, totalWidth);
	int top = verCenter - side;
	int bottom = verCenter + side;
	int left = horCenter - side;
	int right = horCenter + side;


	Rectangle(hdc, left, top, right, bottom);
	TextOut(hdc, roi.left + 5, roi.top + 1, TEXT("Квадрат"), 7);
}

void drawDiamond(HDC& hdc, RECT& roi) {
	int horCenter = (roi.left + roi.right) / 2;
	int verCenter = (roi.top + roi.bottom) / 2;

	Line(hdc, roi.left + 10, verCenter, horCenter, roi.top + 10);
	Line(hdc, horCenter, roi.top + 10, roi.right - 10, verCenter);
	Line(hdc, roi.right - 10, verCenter, horCenter, roi.bottom - 10);
	Line(hdc, horCenter, roi.bottom - 10, roi.left + 10, verCenter);

	TextOut(hdc, roi.left + 5, roi.top + 1, TEXT("Ромб"), 4);
}

void drawEllipse(HDC& hdc, RECT& roi) {
	Ellipse(hdc, roi.left + 10, roi.top + 10, roi.right - 10, roi.bottom - 10);
	TextOut(hdc, roi.left + 5, roi.top + 1, TEXT("Эллипс"), 6);
}

void drawSector(HDC& hdc, RECT& roi) {
	int horCenter = (roi.left + roi.right) / 2;
	int verCenter = (roi.top + roi.bottom) / 2;

	int totalHeight = roi.bottom - roi.top;
	int totalWidth = roi.right - roi.left;

	int radius = 0.45 * min(totalHeight, totalWidth);
	int top = verCenter - radius;
	int bottom = verCenter + radius;
	int left = horCenter - radius;
	int right = horCenter + radius;


	Pie(hdc, left, top, right, bottom,
		left, top, left, verCenter);

	TextOut(hdc, roi.left + 5, roi.top + 1, TEXT("Сектор"), 6);
}

void drawTriangle(HDC& hdc, RECT& roi) {
	int horCenter = (roi.left + roi.right) / 2;
	int verCenter = (roi.top + roi.bottom) / 2;

	int totalHeight = roi.bottom - roi.top;
	int totalWidth = roi.right - roi.left;

	int radius = 0.45 * min(totalHeight, totalWidth);

	int x1 = horCenter + radius * cos(2 * M_PI / 3);
	int y1 = verCenter + radius * sin(2 * M_PI / 3);

	int x2 = horCenter + radius * cos(4 * M_PI / 3);
	int y2 = verCenter + radius * sin(4 * M_PI / 3);

	int x3 = horCenter + radius * cos(6 * M_PI / 3);
	int y3 = verCenter + radius * sin(6 * M_PI / 3);

	Line(hdc, x1, y1, x2, y2);
	Line(hdc, x2, y2, x3, y3);
	Line(hdc, x3, y3, x1, y1);
	TextOut(hdc, roi.left + 5, roi.top + 1, TEXT("Треугольник"), 11);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int nRows = 2;
	int nCols = 3;

	HFONT font;
	font = CreateFontA(16, 0, 0, 0, 0, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, 0, "Arial");

	static std::vector<RECT> rects;
	static std::vector < std::function<void(HDC&, RECT&)> > drawers = {
		drawRect,
		drawSquare,
		drawDiamond,
		drawEllipse,
		drawSector,
		drawTriangle
	};

	static std::vector < LPCWSTR > cursors = {
		IDC_ARROW,
		IDC_WAIT,
		IDC_CROSS,
		IDC_HAND,
		IDC_HELP,
		IDC_IBEAM
	};

	static LPCWSTR cursor;

	switch (message)
	{
	case WM_SETCURSOR:
		if(LOWORD(lParam) == HTCLIENT)
			SetCursor(LoadCursor(NULL, cursor));
		break;
	case WM_DESTROY:
		DeleteObject(hVioletPen);
		DeleteObject(hPinkBrush);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		cursor = cursors[0];
		hVioletPen = CreatePen(PS_SOLID, 2, RGB(59, 18, 35));
		hPinkBrush = CreateSolidBrush(RGB(158, 104, 128));
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);

		SelectObject(hdc, font);

		rects = splitArea(hdc, clientRect, nRows, nCols);

		SelectBrush(hdc, hPinkBrush);
		SelectPen(hdc, hVioletPen);

		for (int i = 0; i < rects.size(); ++i) {
			drawers[i](hdc, rects[i]);
		}


		DrawText(hdc, TEXT("Далецкий Д.А."), -1, &clientRect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

		EndPaint(hwnd, &ps);
		break;
	case WM_MOUSEMOVE:
		int x;
		int y;
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		for (int i = 0; i < rects.size(); ++i) {
			if (x > rects[i].left && x < rects[i].right && y > rects[i].top && y < rects[i].bottom) {
				cursor = cursors[i];
				break;
			}
		}
		break;

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 300;
		lpMMI->ptMinTrackSize.y = 300;
	}
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void Line(HDC hdc, double x1, double y1, double x2, double y2){
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	return;
}
