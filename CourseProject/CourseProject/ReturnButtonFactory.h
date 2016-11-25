#pragma once
class ReturnButtonFactory :	public ButtonFactory
{
	public:
		ReturnButtonFactory();
		~ReturnButtonFactory();
		Button* CreateButton(TCHAR*, HWND, HINSTANCE, LPCWSTR, int, int, int);
};

