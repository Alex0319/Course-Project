#include "stdafx.h"

RecordsButtonFactory::RecordsButtonFactory()
{
}


RecordsButtonFactory::~RecordsButtonFactory()
{
}

Button* RecordsButtonFactory::CreateButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId)
{
	return new RecordsButton(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId);
}