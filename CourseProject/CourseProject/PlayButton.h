#pragma once
class PlayButton :	public Button
{
	public:
		PlayButton();
		PlayButton(TCHAR*,HWND, HINSTANCE, LPCWSTR, int, int, int);
		~PlayButton();
};

