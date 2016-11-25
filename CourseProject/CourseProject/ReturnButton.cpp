#include "stdafx.h"

ReturnButton::ReturnButton()
{
}

ReturnButton::ReturnButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId)
: Button(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId)
{
}

ReturnButton::~ReturnButton()
{
}
