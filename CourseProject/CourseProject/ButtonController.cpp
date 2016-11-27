#include "stdafx.h"

ButtonController::ButtonController()
{
}


ButtonController::~ButtonController()
{
	for (auto it = buttonsMap.begin(); it != buttonsMap.end(); it++)
		delete it->second;
	buttonsMap.clear();
}


void ButtonController::UpdateMenuButtons(HWND hWnd, HINSTANCE hInst, HDC hdc)
{
//	BitmapModificator::CreateBitmapMask(hWnd, hBitmap, hdc, RGB(255, 255, 255));
}

POINT ButtonController::GetButtonPosition(int buttonId,int* x,int* y,BITMAP bitmapInfo)
{
	POINT buttonPosition;
	switch (buttonId)
	{
		case IDM_PLAY:
			*x = (WINDOW_WIDTH - bitmapInfo.bmWidth) / 2;
			buttonPosition.x = *x;
			buttonPosition.y = *y;
			*y += bitmapInfo.bmHeight + 2;
			break;
		case IDM_RECORDS:
			buttonPosition.x = *x;
			buttonPosition.y = *y;
			*x +=  bitmapInfo.bmWidth + 5;
			break;
		case IDM_CLOSE:
			buttonPosition.x = *x;
			buttonPosition.y = *y;
			break;
/*		case IDM_PLAY2:
			*x = (WINDOW_WIDTH - bitmapInfo.bmWidth) / 2;
			*y =  WINDOW_HEIGHT / 4;
			break;*/
		default:
			break;
	}
	return buttonPosition;
}

void ButtonController::CreateButtons(HWND hwndParent, HINSTANCE hInst)
{
/*	int buttonStartCoordinateX = 0, buttonStartCoordinateY = WINDOW_HEIGHT / 3;
	for (int i = 0; i < mainMenuButtonsCount; i++)
	{
		BITMAP bitmapInfo;
		HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(MAKEINTRESOURCE(IDB_PLAY + i)));
		GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
		POINT buttonPosition = GetButtonPosition(IDM_PLAY + i, &buttonStartCoordinateX, &buttonStartCoordinateY, bitmapInfo);
		buttonsMap.insert(std::pair<int, Button*>(IDM_PLAY + i, new Button(hwndParent, hInst,WS_CHILD | WS_VISIBLE, hBitmap, buttonPosition.x, buttonPosition.y, IDM_PLAY + i)));
	}*/

}
