#include "stdafx.h"

RecordsButton::RecordsButton()
{
}

RecordsButton::RecordsButton(TCHAR* szButtonName, HWND hwndParent, HINSTANCE hInst, LPCWSTR lpBitmapName, int x, int y, int buttonId)
: Button(szButtonName, hwndParent, hInst, lpBitmapName, x, y, buttonId)
{
}


RecordsButton::~RecordsButton()
{
}
