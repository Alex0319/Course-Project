#include "stdafx.h"

VerticalLine::VerticalLine()
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

VerticalLine::VerticalLine(std::string figureInfo) :Figure(figureInfo)
{

}

VerticalLine::~VerticalLine()
{
}

int VerticalLine::GetBlocksCountInColumn()
{
	return blocksCount;
}

int VerticalLine::GetBlocksCountInRow()
{
	return 1;
}

void VerticalLine::DrawFigure(HDC hdc, int x, int y, int blockSize)
{
	SetRectStartPoint(x, y);
	for (int i = 0; i < blocksCount; i++)
	{
		figureBlock.DrawBlock(hdc, figureColor, x, y, blockSize);
		y += blockSize;
	}
	SetRectEndPoint(x + blockSize, y);
}

int VerticalLine::SetFigureOnChoosePlace(BlockColors(*colorsTable)[BLOCKS_COUNT], int blockNumber)
{
	int blocksCountInRow = GetBlocksCountInColumn();
	int row = blockNumber / BLOCKS_COUNT - blocksCountInRow + 1, column = blockNumber % BLOCKS_COUNT;
	return SetFigure(colorsTable, row, column, blocksCountInRow, GetBlocksCountInRow());
}

bool VerticalLine::CheckBlock(BlockColors(*colorsTable)[BLOCKS_COUNT], int blockNumber)
{
	int blocksCountInRow = GetBlocksCountInColumn();
	int row = blockNumber / BLOCKS_COUNT - blocksCountInRow + 1, column = blockNumber % BLOCKS_COUNT;
	return Check(colorsTable, row, column, blocksCountInRow, GetBlocksCountInRow());
}
