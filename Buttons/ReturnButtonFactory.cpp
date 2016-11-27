#include "stdafx.h"

ReturnButtonFactory::ReturnButtonFactory()
{
}


ReturnButtonFactory::~ReturnButtonFactory()
{
}

Button* ReturnButtonFactory::CreateButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId)
{
	return new ReturnButton(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId);
}
