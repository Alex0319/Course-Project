#include "stdafx.h"

Button::Button()
{
}

Button::Button(HWND hwndParent, HINSTANCE hInst,DWORD dwStyle, HBITMAP bitmap, int x, int y, int buttonId)
{
	hBitmap = bitmap;
	GetObject(hBitmap, sizeof(BITMAP),&bitmapInfo);
	hButton = CreateWindow(WC_BUTTON, NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP,
		x, y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, hwndParent, (HMENU)buttonId, hInst, 0);
	SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
}

Button::~Button()
{
}

HWND Button::GetButtonHwnd()
{
	return hButton;
}

BITMAP Button::GetButtonBitmapInfo()
{
	return bitmapInfo;
}