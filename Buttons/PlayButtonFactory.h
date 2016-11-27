#pragma once
class PlayButtonFactory :	public ButtonFactory
{
	public:
		PlayButtonFactory();
		~PlayButtonFactory();
		Button* CreateButton(TCHAR*, HWND, HINSTANCE, LPCWSTR, int, int, int);
};

