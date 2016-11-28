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

bool Angle::CheckBlocks(BlockColors(*colorsTable)[BLOCKS_COUNT], int* modificateIndex,int constIndex, int startBlockIndex,bool isRowIndex)
{
	for (*modificateIndex = startBlockIndex; *modificateIndex < startBlockIndex + blocksCountInColumn; (*modificateIndex)++)
		if (isRowIndex)
		{
			if (colorsTable[*modificateIndex][constIndex] != DEFAULT)
				return false;
		}
		else
			if (colorsTable[constIndex][*modificateIndex] != DEFAULT)
				return false;
	return true;
}

bool Angle::CheckPlace(BlockColors(*colorsTable)[BLOCKS_COUNT], int row, int column, int blocksCountInRow, int blocksCountInColumn)
{
	int i = 0, j = 0;
	switch (angleType)
	{
		case LEFTTOP: return CheckBlocks(colorsTable, &i,column,row,true) && CheckBlocks(colorsTable, &j,row,column,false);
		case LEFTBOTTOM: return CheckBlocks(colorsTable, &i, column, row, true) && CheckBlocks(colorsTable, &j, i-1, column, false);
		case RIGHTTOP: return CheckBlocks(colorsTable, &j, row, column, false) && CheckBlocks(colorsTable, &i, j-1, row, true);
		case RIGHTBOTTOM: return CheckBlocks(colorsTable, &i, column, row, true) && CheckBlocks(colorsTable, &j, i - 1, column, false);
	}
	return true;
}

void Angle::SetBlockColors(BlockColors(*colorsTable)[BLOCKS_COUNT], int* modificateIndex, int constIndex, int startBlockIndex, bool isRowIndex)
{
	for (*modificateIndex = startBlockIndex; *modificateIndex < startBlockIndex + blocksCountInColumn; (*modificateIndex)++)
		if (isRowIndex)
			colorsTable[*modificateIndex][constIndex] = figureColor;
		else
			colorsTable[constIndex][*modificateIndex] = figureColor;
}

int Angle::SetFigure(BlockColors(*colorsTable)[BLOCKS_COUNT], int row, int column, int blocksCountInRow, int blocksCountInColumn)
{
	int i = 0, j = 0;
	if (CheckPlace(colorsTable, row, column, blocksCountInRow, blocksCountInColumn))
	{
		switch (angleType)
		{
			case LEFTTOP:
				SetBlockColors(colorsTable, &i, column, row, true);
				SetBlockColors(colorsTable, &j, row, column, false);
				break;
			case LEFTBOTTOM:
				SetBlockColors(colorsTable, &i, column, row, true);
				SetBlockColors(colorsTable, &j, i - 1, column, false);
				break;
			case RIGHTTOP:
				SetBlockColors(colorsTable, &j, row, column, false);
				SetBlockColors(colorsTable, &i, j - 1, row, true);
				break;
			case RIGHTBOTTOM:
				SetBlockColors(colorsTable, &i, column, row, true);
				SetBlockColors(colorsTable, &j, i - 1, column, false);
				break;
		}
		return blocksCount;
	}
	return 0;
}

int Angle::SetFigureOnChoosePlace(BlockColors(*colorsTable)[BLOCKS_COUNT], int blockNumber)
{
	int blocksCount= GetBlocksCountInRow();
	int row = 0, column = 0;
	row = blockNumber / BLOCKS_COUNT - blocksCount + 1;
	if (angleType != RIGHTBOTTOM)
		column = blockNumber % BLOCKS_COUNT;
	else
		column = blockNumber % BLOCKS_COUNT + blocksCount - 1;
	return SetFigure(colorsTable, row, column, blocksCount, blocksCount);
}
