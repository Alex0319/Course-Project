#include "stdafx.h"

Square::Square()
{
	srand(time(0));
	if (rand() % 4)
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

Square::Square(std::string figureInfo) :Figure(figureInfo)
{
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

int Square::SetFigureOnChoosePlace(BlockColors(*colorsTable)[BLOCKS_COUNT], int blockNumber)
{
	int blocksCountInRow = GetBlocksCountInRow();
	int row = blockNumber / BLOCKS_COUNT - blocksCountInRow + 1, column = blockNumber % BLOCKS_COUNT;
	return SetFigure(colorsTable, row, column, blocksCountInRow, blocksCountInRow);
}

bool Square::CheckBlock(BlockColors(*colorsTable)[BLOCKS_COUNT], int blockNumber)
{
	int blocksCountInRow = GetBlocksCountInRow();
	int row = blockNumber / BLOCKS_COUNT - blocksCountInRow + 1, column = blockNumber % BLOCKS_COUNT;
	return Check(colorsTable, row, column, blocksCountInRow, blocksCountInRow);
}
