#include "stdafx.h"

BitmapModificator::BitmapModificator()
{
}


BitmapModificator::~BitmapModificator()
{
}

void BitmapModificator::CreateBitmapMask(HWND hWnd, HBITMAP hbmColor, HDC hdc, COLORREF crTransparent)
{
	HDC hdcMem, hdcMem2;
	HBITMAP hbmMask;
	BITMAP bm;
	GetObject(hbmColor, sizeof(BITMAP), &bm);
	hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	hdcMem = CreateCompatibleDC(hdc);
	hdcMem2 = CreateCompatibleDC(hdc);

	HBITMAP prevHbmColor = SelectBitmap(hdcMem, hbmColor);
	HBITMAP prevHbmColor2 = SelectBitmap(hdcMem2, hbmMask);

	SetBkColor(hdcMem, crTransparent);
	BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);
	BitBlt(hdc, 100, 50, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCAND);
	BitBlt(hdc, 100, 50, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCPAINT);


	SelectObject(hdcMem, prevHbmColor);
	SelectObject(hdcMem2, prevHbmColor2);

	DeleteObject(hdcMem);
	DeleteObject(hdcMem2);
}
