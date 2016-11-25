#include "stdafx.h"

HomeButtonFactory::HomeButtonFactory()
{
}

HomeButtonFactory::~HomeButtonFactory()
{
}

Button* HomeButtonFactory::CreateButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId)
{
	return new HomeButton(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId);
}
