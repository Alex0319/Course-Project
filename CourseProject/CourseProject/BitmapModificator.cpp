#include "stdafx.h"

BitmapModificator::BitmapModificator()
{
}


BitmapModificator::~BitmapModificator()
{
}

int BitmapModificator::CreateBitmapMask(HWND hWnd, HBITMAP hbmColor,BITMAP bm, HDC hdc, COLORREF crTransparent,int x,int y)
{
	HDC hdcMem, hdcMem2;
	HBITMAP hbmMask;
	hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	hdcMem = CreateCompatibleDC(hdc);
	hdcMem2 = CreateCompatibleDC(hdc);

	HBITMAP prevHbmColor = SelectBitmap(hdcMem, hbmColor);
	HBITMAP prevHbmColor2 = SelectBitmap(hdcMem2, hbmMask);

	SetBkColor(hdcMem, crTransparent);
	BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);
	BitBlt(hdc, x - bm.bmWidth/2, y, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCAND);
	BitBlt(hdc, x - bm.bmWidth / 2, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCPAINT);


	SelectObject(hdcMem, prevHbmColor);
	SelectObject(hdcMem2, prevHbmColor2);

	DeleteObject(hdcMem);
	DeleteObject(hdcMem2);
	return bm.bmWidth;
}
