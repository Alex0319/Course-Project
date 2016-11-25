#include "stdafx.h"

HomeButton::HomeButton()
{
}

HomeButton::HomeButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId)
: Button(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId)
{
}

HomeButton::~HomeButton()
{
}
