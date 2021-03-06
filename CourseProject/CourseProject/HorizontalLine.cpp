#include "stdafx.h"

HorizontalLine::HorizontalLine()
{
	srand(time(0));
	blocksCount = rand() % 5 + 1;
	switch (blocksCount)
	{
		case 1: figureColor = BlockColors::PURPLE;
			break;
		case 2: figureColor = BlockColors::YELLOW;
			break;
		case 3: figureColor = BlockColors::ORANGE;
			break;
		case 4: figureColor = BlockColors::PINK;
			break;
		case 5: figureColor = BlockColors::RED;
			break;
	}
}

HorizontalLine::HorizontalLine(std::string figureInfo) :Figure(figureInfo)
{
}


HorizontalLine::~HorizontalLine()
{
}

int HorizontalLine::GetBlocksCountInColumn()
{
	return 1;
}

int HorizontalLine::GetBlocksCountInRow()
{
	return blocksCount;
}

void HorizontalLine::DrawFigure(HDC hdc, int x, int y,int blockSize)
{
	SetRectStartPoint(x, y);
	for (int i = 0; i < blocksCount; i++)
	{
		figureBlock.DrawBlock(hdc, figureColor, x, y, blockSize);
		x += blockSize;
	}
	SetRectEndPoint(x, y + blockSize);
}

int HorizontalLine::SetFigureOnChoosePlace(BlockColors(*colorsTable)[BLOCKS_COUNT], int blockNumber)
{
	int row = blockNumber / BLOCKS_COUNT, column = blockNumber % BLOCKS_COUNT;
	return SetFigure(colorsTable, row, column, GetBlocksCountInColumn(), GetBlocksCountInRow());
}

bool HorizontalLine::CheckBlock(BlockColors(*colorsTable)[BLOCKS_COUNT], int blockNumber)
{
	int row = blockNumber / BLOCKS_COUNT, column = blockNumber % BLOCKS_COUNT;
	return Check(colorsTable, row, column, GetBlocksCountInColumn(), GetBlocksCountInRow());
}
