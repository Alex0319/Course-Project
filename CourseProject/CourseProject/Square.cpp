#include "stdafx.h"

Square::Square()
{
	srand(time(0));
	if (rand() % 3)
	{
		blocksCount = 4;
		figureColor = BlockColors::LIGHTGREEN;
	}
	else
	{
		blocksCount = 9;
		figureColor = BlockColors::GREEN;
	}
}

Square::~Square()
{
}

void Square::DrawFigure(HDC hdc, int x, int y, int blockSize)
{
	SetRectStartPoint(x, y);
	int figureSize = sqrt(blocksCount);
	for (int i = 0; i < figureSize; i++)
	{
		int temp = x;
		for (int j = 0; j < figureSize; j++)
		{
			figureBlock.DrawBlock(hdc, figureColor, x, y, blockSize);
			x += blockSize;
		}
		if (i!=figureSize-1)
			x = temp;
		y += blockSize;
	}
	SetRectEndPoint(x, y);
}

int Square::GetBlocksCountInColumn()
{
	return sqrt(blocksCount);
}

int Square::GetBlocksCountInRow()
{
	return sqrt(blocksCount);
}