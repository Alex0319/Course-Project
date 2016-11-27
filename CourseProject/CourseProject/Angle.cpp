#include "stdafx.h"

Angle::Angle()
{
	srand(time(0));
	if (rand() % 2)
	{
		blocksCount = 3;
		figureColor = BlockColors::DARKGREEN;
	}
	else
	{
		blocksCount = 5;
		figureColor = BlockColors::BLUE;
	}
	switch (rand() % 3 + 1)
	{
		case 1: angleType = LEFTTOP;
			break;
		case 2: angleType = LEFTBOTTOM;
			break;
		case 3: angleType = RIGHTTOP;
			break;
		case 4: angleType = RIGHTBOTTOM;
			break;
	}
	blocksCountInColumn = 0.5*blocksCount + 0.5;
}


Angle::~Angle()
{
}

void Angle::DrawLine(HDC hdc, int x, int y,int blocksCount,int blockSize)
{
	for (int i = 0; i < blocksCount; i++)
	{
		figureBlock.DrawBlock(hdc, figureColor, x, y, blockSize);
		x += blockSize;
	}
	SetRectEndPoint(x, 0);
}

void Angle::DrawColumn(HDC hdc, int x, int y, int blocksCount,int blockSize)
{
	for (int i = 0; i < blocksCount; i++)
	{
		figureBlock.DrawBlock(hdc, figureColor, x, y, blockSize);
		y += blockSize;
	}
	SetRectEndPoint(0, y);
}

void Angle::DrawFigure(HDC hdc, int x, int y,int blockSize)
{
	SetRectStartPoint(x, y);
	int blocksCountToDraw = blocksCountInColumn - 1;
	switch (angleType)
	{
		case LEFTTOP: 
			DrawColumn(hdc, x, y, blocksCountInColumn, blockSize);
			DrawLine(hdc, x + blockSize, y, blocksCountToDraw, blockSize);
			break;
		case LEFTBOTTOM: 
			DrawColumn(hdc, x, y, blocksCountInColumn, blockSize);
			DrawLine(hdc, x + blockSize, y + blocksCountToDraw * blockSize, blocksCountToDraw,blockSize);
			break;
		case RIGHTTOP: 
			DrawLine(hdc, x, y, blocksCountInColumn, blockSize);
			DrawColumn(hdc, x + blocksCountToDraw * blockSize, y + blockSize, blocksCountToDraw, blockSize);
			break;
		case RIGHTBOTTOM:
			DrawColumn(hdc, x + blocksCountToDraw * blockSize, y, blocksCountInColumn, blockSize);
			DrawLine(hdc, x, y + blocksCountToDraw * blockSize, blocksCountToDraw, blockSize);
			break;
	}
}

int Angle::GetBlocksCountInColumn()
{
	return blocksCountInColumn;
}

int Angle::GetBlocksCountInRow()
{
	return blocksCountInColumn;
}