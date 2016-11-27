#pragma once

class ButtonController
{
	public:
		ButtonController();
		~ButtonController();
		void CreateButtons(HWND, HINSTANCE);
		void UpdateMenuButtons(HWND, HINSTANCE, HDC);
	private:
		const int mainMenuButtonsCount = 3;
		const int closeButtonsCount = 3;
		std::map <int, Button*> buttonsMap;
		POINT GetButtonPosition(int, int*,int*, BITMAP);
};

