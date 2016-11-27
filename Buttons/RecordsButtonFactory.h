#pragma once
class RecordsButtonFactory :	public ButtonFactory
{
	public:
		RecordsButtonFactory();
		~RecordsButtonFactory();
		Button* CreateButton(TCHAR*, HWND, HINSTANCE, LPCWSTR, int, int, int);
};

