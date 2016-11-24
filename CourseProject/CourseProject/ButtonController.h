#pragma once

class ButtonController
{
	public:
		ButtonController();
		~ButtonController();
		void UpdateMenuButtons(HWND hWnd, HINSTANCE hInst, HDC hdc);
	private:
		int menuButtonsCount = 0;
		const int closeButtonsCount = 4;
		std::map <int, HWND> buttonsHwndMap;
		void CreateBitmapMask(HWND hWnd, HBITMAP hbmColor, HDC hdc, COLORREF crTransparent);
};

