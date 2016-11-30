#pragma once
class BitmapModificator
{
	public:
		BitmapModificator();
		~BitmapModificator();
		static int CreateBitmapMask(HWND hWnd, HBITMAP hbmColor,BITMAP bm, HDC hdc, COLORREF crTransparent,int,int);
};

