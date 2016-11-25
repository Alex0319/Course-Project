#pragma once
class HomeButton : public Button
{
	public:
		HomeButton();
		HomeButton(TCHAR*, HWND, HINSTANCE, LPCWSTR, int, int, int);
		~HomeButton();
};
