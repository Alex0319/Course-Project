#pragma once
class HomeButtonFactory : public ButtonFactory
{
	public:
		HomeButtonFactory();
		~HomeButtonFactory();
		Button* CreateButton(TCHAR*, HWND, HINSTANCE, LPCWSTR, int, int, int);
};

