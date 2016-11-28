#include "stdafx.h"


FieldBlock::FieldBlock()
{
}


FieldBlock::~FieldBlock()
{
}

void FieldBlock::SetBlockRect(int x, int y)
{
	blockRect.left = x;
	blockRect.top = y;
	blockRect.right = x + BLOCK_SIZE;
	blockRect.bottom = y + BLOCK_SIZE;
}

RECT FieldBlock::GetFieldBlockRect()
{
	return blockRect;
}

void FieldBlock::DrawBlock(HDC hdc, COLORREF brushColor, int x, int y, int blockSize)
{
	SetBlockRect(x, y);
	hBrush = CreateSolidBrush(brushColor);
	HBRUSH oldBrush = SelectBrush(hdc, hBrush);
	RoundRect(hdc, x, y, x + blockSize, y + blockSize, ellipseSize, ellipseSize);
	SelectBrush(hdc, oldBrush);
	DeleteObject(hBrush);
}