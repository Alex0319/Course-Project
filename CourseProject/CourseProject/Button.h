#pragma once
class Button
{
	public:
		Button();
		Button(TCHAR*,HWND, HINSTANCE, LPCWSTR, int, int, int);
		~Button();
//		virtual void HideButton(HDC hdc)=0;
	protected:
		HBITMAP hBitmap;
		HWND hButton;
		BITMAP bitmapInfo;
	private:
		void CreateBitmapMask(HWND, HBITMAP, BITMAP, HDC, COLORREF);
};

