#include "stdafx.h"

ButtonController::ButtonController()
{

}


ButtonController::~ButtonController()
{
}

void ButtonController::CreateBitmapMask(HWND hWnd,HBITMAP hbmColor,HDC hdc, COLORREF crTransparent)
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

void ButtonController::UpdateMenuButtons(HWND hWnd, HINSTANCE hInst,HDC hdc)
{
//	for (int i = 0; i < 1; i++)
//	{
	
		HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLAY2));
		CreateBitmapMask(hWnd,hBitmap,hdc,RGB(255,255,255));
}