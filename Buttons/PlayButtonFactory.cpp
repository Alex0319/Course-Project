#include "stdafx.h"

PlayButtonFactory::PlayButtonFactory()
{
}


PlayButtonFactory::~PlayButtonFactory()
{
}

Button* PlayButtonFactory::CreateButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId)
{
	return new PlayButton(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId);
}
