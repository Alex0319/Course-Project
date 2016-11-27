#pragma once
class BitmapModificator
{
	public:
		BitmapModificator();
		~BitmapModificator();
		static void CreateBitmapMask(HWND hWnd, HBITMAP hbmColor, HDC hdc, COLORREF crTransparent);
};

