#include "stdafx.h"

Button::Button()
{
}

Button::Button(TCHAR* szButtonName,HWND hwndParent,HINSTANCE hInst, LPCWSTR lpBitmapName,int x,int y,int buttonId)
{
	hBitmap = LoadBitmap(hInst, lpBitmapName);
	GetObject(hBitmap, sizeof(BITMAP),&bitmapInfo);
	hButton = CreateWindow(szButtonName, NULL, WS_CHILD | WS_VISIBLE,
		x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, hwndParent, (HMENU)buttonId, hInst, 0);
	HRGN hRgn = CreateRoundRectRgn(x, y, x + bitmapInfo.bmWidth, y + bitmapInfo.bmHeight, bitmapInfo.bmWidth, bitmapInfo.bmHeight);
	SetWindowRgn(hButton, hRgn, TRUE);
}

Button::~Button()
{
}

void Button::CreateBitmapMask(HWND hWnd, HBITMAP hbmColor,BITMAP bitmap, HDC hdc, COLORREF crTransparent)
{
	HDC hdcMem, hdcMem2;
	HBITMAP hbmMask;
	hbmMask = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, NULL);
	hdcMem = CreateCompatibleDC(hdc);
	hdcMem2 = CreateCompatibleDC(hdc);

	HBITMAP prevHbmColor = SelectBitmap(hdcMem, hbmColor);
	HBITMAP prevHbmColor2 = SelectBitmap(hdcMem2, hbmMask);

	SetBkColor(hdcMem, crTransparent);
	BitBlt(hdcMem2, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem2, 0, 0, SRCINVERT);
	BitBlt(hdc, 100, 50, bitmap.bmWidth, bitmap.bmHeight, hdcMem2, 0, 0, SRCAND);
	BitBlt(hdc, 100, 50, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCPAINT);


	SelectObject(hdcMem, prevHbmColor);
	SelectObject(hdcMem2, prevHbmColor2);

	DeleteObject(hdcMem);
	DeleteObject(hdcMem2);
}
