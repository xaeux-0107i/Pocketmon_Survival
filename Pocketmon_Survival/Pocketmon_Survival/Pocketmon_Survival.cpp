#pragma comment (lib, "msimg32.lib")
#include <windows.h>
#include "resource.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Pocketmon Survival";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)

{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

int C_direction = 0;
int animationNum = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC, mDC, characterDC;
	static HBITMAP hBitmapCharacter, hBitmapMDC;
	RECT rt;

	switch (uMsg) {
	case WM_CREATE: {
		SetTimer(hWnd, 1, 500, NULL);
		hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	}
				  break;
	case WM_PAINT: {
		GetClientRect(hWnd, &rt);
		hDC = BeginPaint(hWnd, &ps);

		// 주인공 포켓몬 이미지 가져오기
		if (C_direction == 0) {
			if (animationNum == 0) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			}
			else if (animationNum == 1) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			}
		}
		else if (C_direction == 1) {
			if (animationNum == 0) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
			}
			else if (animationNum == 1) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
			}
		}
		else if (C_direction == 2) {
			if (animationNum == 0) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
			}
			else if (animationNum == 1) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
			}
		}
		else if (C_direction == 3) {
			if (animationNum == 0) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
			}
			else if (animationNum == 1) {
				hBitmapCharacter = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
			}
		}

		characterDC = CreateCompatibleDC(hDC);
		mDC = CreateCompatibleDC(hDC);
		hBitmapMDC = CreateCompatibleBitmap(mDC, rt.right, rt.bottom);
		SelectObject(characterDC, hBitmapCharacter);
		SelectObject(mDC, hBitmapMDC);
		FillRect(mDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));

		BitBlt(hDC, 0, 0, 800, 600, mDC, 0, 0, SRCCOPY);
		TransparentBlt(hDC, 400, 300, 50, 50, characterDC, 0, 0, 20, 20, RGB(255, 255, 255));

		DeleteDC(characterDC);
		DeleteDC(mDC);
		DeleteObject(hBitmapCharacter);
		DeleteObject(hBitmapMDC);
		EndPaint(hWnd, &ps);
	}
				 break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_UP:
			C_direction = 1;
			break;
		case VK_DOWN:
			C_direction = 0;
			break;
		case VK_LEFT:
			C_direction = 2;
			break;
		case VK_RIGHT:
			C_direction = 3;
			break;
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			if (animationNum == 0) {
				animationNum = 1;
			}
			else {
				animationNum = 0;
			}
			InvalidateRect(hWnd, NULL, false);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}