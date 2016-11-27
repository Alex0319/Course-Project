#include "stdafx.h"

Block::Block()
{
}


Block::~Block()
{
}

void Block::DrawBlock(HDC hdc, COLORREF brushColor,int x, int y,int blockSize)
{
	hBrush = CreateSolidBrush(brushColor);
	HBRUSH oldBrush = SelectBrush(hdc, hBrush);
	RoundRect(hdc, x, y, x + blockSize, y + blockSize, ellipseSize, ellipseSize);
	SelectBrush(hdc, oldBrush);
	DeleteObject(hBrush);
}