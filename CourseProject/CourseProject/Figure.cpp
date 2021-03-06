#include "stdafx.h"

Figure::Figure()
{
}

Figure::~Figure()
{
}

Figure::Figure(std::string figureInfo)
{
	COLORREF color=0;
	sscanf_s(figureInfo.c_str(), "%d_%d_%d_%d", &((DWORD)color), &blocksCount, &(figureRect.left), &(figureRect.top));
	figureColor = (BlockColors)color;
}

std::string Figure::GetFigureProperties()
{
	COLORREF color = figureColor;
	char propertiesStr[MAX_PROPERTIES_SIZE];
	ZeroMemory(propertiesStr, MAX_PROPERTIES_SIZE);
	sprintf_s(propertiesStr, sizeof(propertiesStr), "%d_%d_%d_%d", (DWORD)color, blocksCount, figureRect.left, figureRect.top);
	return std::string(propertiesStr);
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

bool Figure::Check(BlockColors(*colorsTable)[BLOCKS_COUNT], int row, int column, int blocksCountInRow, int blocksCountInColumn)
{
	if (row + blocksCountInRow > BLOCKS_COUNT || column + blocksCountInColumn > BLOCKS_COUNT || row<0 || column<0)
		return false;
	for (int i = row; i < row + blocksCountInRow; i++)
		for (int j = column; j < column + blocksCountInColumn; j++)
			if (colorsTable[i][j] != DEFAULT)	
				return false;
	return true;
}

int Figure::SetFigure(BlockColors(*colorsTable)[BLOCKS_COUNT], int row, int column, int blocksCountInRow, int blocksCountInColumn)
{
	if (Check(colorsTable, row, column, blocksCountInRow, blocksCountInColumn))
	{
		for (int i = row; i < row + blocksCountInRow; i++)
			for (int j = column; j < column + blocksCountInColumn; j++)
				colorsTable[i][j] = figureColor;
		return blocksCount;
	}
	return 0;
}