#include "stdafx.h"

Figure::Figure()
{
}

Figure::~Figure()
{
}

void Figure::SetRectStartPoint(int x, int y)
{
	figureRect.left = x;
	figureRect.top = y;
}

void Figure::SetRectEndPoint(int x, int y)
{
	if (x != 0)
		figureRect.right = x;
	if (y != 0)
		figureRect.bottom = y;
}

RECT Figure::GetFigureRect()
{
	return figureRect;
}

bool Figure::CheckResultRect(RECT resultRect, RECT figureRect)
{
	int maxAllowedLimit = BLOCK_SIZE / 3;
	if (abs(figureRect.left - resultRect.left) >= maxAllowedLimit || abs(figureRect.top - resultRect.top) >= maxAllowedLimit ||
		abs(figureRect.right - resultRect.right) >= maxAllowedLimit || abs(figureRect.bottom - resultRect.bottom) >= maxAllowedLimit)
		return false;
	return true;
}

bool Figure::CheckPlaceForFigure(RECT fieldRect)
{
	RECT resultRect;
	if (!(IntersectRect(&resultRect, &fieldRect, &figureRect) && CheckResultRect(resultRect,figureRect)))
		return false;
	return true;
}

bool Figure::CheckPlace(BlockColors(*colorsTable)[BLOCKS_COUNT], int row, int column, int blocksCountInRow, int blocksCountInColumn)
{
	for (int i = row; i < row + blocksCountInRow; i++)
		for (int j = column; j < column + blocksCountInColumn; j++)
			if (colorsTable[i][j] != DEFAULT)	
				return false;
	return true;
}

int Figure::SetFigure(BlockColors(*colorsTable)[BLOCKS_COUNT], int row, int column, int blocksCountInRow, int blocksCountInColumn)
{
	if (CheckPlace(colorsTable, row, column, blocksCountInRow, blocksCountInColumn))
	{
		for (int i = row; i < row + blocksCountInRow; i++)
			for (int j = column; j < column + blocksCountInColumn; j++)
				colorsTable[i][j] = figureColor;
		return blocksCount;
	}
	return 0;
}