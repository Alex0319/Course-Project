#pragma once
class Button
{
	public:
		Button();
		Button(HWND, HINSTANCE,DWORD, HBITMAP, int, int, int);
		~Button();
		HWND GetButtonHwnd();
		BITMAP GetButtonBitmapInfo();
//		virtual void HideButton(HDC hdc)=0;
	private:
		HBITMAP hBitmap;
		HWND hButton;
		BITMAP bitmapInfo;
};

