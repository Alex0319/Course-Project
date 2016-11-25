#pragma once
class ButtonFactory
{
	public:
		ButtonFactory();
		~ButtonFactory();
		virtual Button* CreateButton(TCHAR*, HWND, HINSTANCE, LPCWSTR, int, int, int) = 0;
};

