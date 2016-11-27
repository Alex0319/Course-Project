#include "stdafx.h"

PlayButton::PlayButton()
{
}

PlayButton::PlayButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId) 
			: Button(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId)
{
}

PlayButton::~PlayButton()
{
}
