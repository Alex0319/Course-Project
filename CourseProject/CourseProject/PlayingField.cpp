#include "stdafx.h"

PlayingField::PlayingField()
{
	fieldState = CREATE;
	figureFactories.push_back(new SquareFactory);
	figureFactories.push_back(new HorizontalLineFactory);
	figureFactories.push_back(new VerticalLineFactory);
	figureFactories.push_back(new AngleFactory);
	fieldRect = { BLOCK_SIZE, FIELD_START, BLOCK_SIZE*(BLOCKS_COUNT + 1), PLAYING_FIELD };
	hPen = GetStockPen(NULL_PEN);
	for (int i = 0; i < BLOCKS_COUNT;i++)
		for (int j = 0; j < BLOCKS_COUNT; j++)
			blockTable[i][j] = DEFAULT;
}

PlayingField::~PlayingField()
{
	DeleteObject(hPen);
	ClearFiguresVector();
	for (auto it = figureFactories.begin(); it != figureFactories.end();it++)
		delete *it;
	figureFactories.clear();
}

int PlayingField::SearchFullRows()
{
	int blocksCount=0,j=0;
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		for (j = 0; j < BLOCKS_COUNT; j++)
			if (blockTable[i][j] == DEFAULT)
				break;
		if (j == BLOCKS_COUNT)
		{
			for (j = 0; j < BLOCKS_COUNT; j++)
				blockTable[i][j] = DEFAULT;
			blocksCount += BLOCKS_COUNT;
		}
	}
	return blocksCount;
}

int PlayingField::SearchFullColumns()
{
	int blocksCount = 0, i = 0;
	for (int j = 0; j < BLOCKS_COUNT; j++)
	{
		for (i = 0; i< BLOCKS_COUNT; i++)
		if (blockTable[i][j] == DEFAULT)
			break;
		if (j == BLOCKS_COUNT)
		{
			for (j = 0; j < BLOCKS_COUNT; j++)
				blockTable[i][j] = DEFAULT;
			blocksCount += BLOCKS_COUNT;
		}
	}
	return blocksCount;
}

void PlayingField::ClearFiguresVector()
{
	for (auto it = figures.begin(); it != figures.end(); it++)
		delete *it;
	if (!figures.empty())
		std::vector<Figure*>().swap(figures);
}

void PlayingField::RemoveFigure()
{
	for (int i = 0; i < figures.size();i++)
		if (chooseFigure == figures[i])
		{
			figures.erase(figures.begin() + i);
			if (!figures.empty())
				std::vector<Figure*>(figures).swap(figures);
		}
}

void PlayingField::PaintPlayingField(HDC hdc)
{
	int currentX = fieldRect.left, currentY = fieldRect.top;
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		for (int j = 0; j < BLOCKS_COUNT; j++)
		{
			blocks[i][j].DrawBlock(hdc, blockTable[i][j], currentX, currentY, BLOCK_SIZE);
			currentX += BLOCK_SIZE;
		}
		currentX = BLOCK_SIZE;
		currentY += BLOCK_SIZE;
	}
}

bool PlayingField::CheckClientClick(POINT point)
{
	for (int i = 0; i < figures.size(); i++)
		if (PtInRect(&(figures[i]->GetFigureRect()), point))
		{
			chooseFigure = figures[i];
			return true;
		}
	return false;
}

bool PlayingField::CheckFigureChoose()
{
	if (chooseFigure != NULL)
		return true;
	return false;
}

void PlayingField::RepaintOtherFigures(HDC hdc)
{
	for (int i=0; i<figures.size(); i++)
		if (chooseFigure == NULL || chooseFigure != figures[i])
		{
			RECT figureRect = figures[i]->GetFigureRect();
			figures[i]->DrawFigure(hdc, figureRect.left, figureRect.top, BLOCK_SIZE_SMALL);
		}
}

void PlayingField::RepaintChooseFigure(HDC hdc,int mouseX,int mouseY)
{
	if (chooseFigure != NULL)
	{
		RECT figureRect = chooseFigure->GetFigureRect();
		if (oldFigureStartPoint.x == 0 && oldFigureStartPoint.y == 0)
		{
			oldFigureStartPoint.x = figureRect.left;
			oldFigureStartPoint.y = figureRect.top;
		}
		int figureWidth = figureRect.right - figureRect.left, figureHeight = figureRect.bottom - figureRect.top;
		chooseFigure->DrawFigure(hdc, mouseX - figureWidth / 2, mouseY - figureHeight - 2, BLOCK_SIZE - 2);
	}
}

void PlayingField::CreateNewFigures(HDC hdc)
{
	srand(time(0));
	ClearFiguresVector();
	int currentX = BLOCK_SIZE_SMALL, currentY = PLAYING_FIELD;
	for (int i = 0; i < newFiguresCount; i++)
	{
		figures.push_back(figureFactories[rand() % figureFactories.size()]->CreateFigure());
		currentX += (NEW_FIGURE_WIDTH - BLOCK_SIZE_SMALL*figures.back()->GetBlocksCountInRow()) / 2;
		int a = NEW_FIGURE_HEIGHT - BLOCK_SIZE_SMALL*figures.back()->GetBlocksCountInColumn();
		currentY += (NEW_FIGURE_HEIGHT - BLOCK_SIZE_SMALL*figures.back()->GetBlocksCountInColumn()) / 4;
		figures.back()->DrawFigure(hdc, currentX, currentY, BLOCK_SIZE_SMALL);
		currentX = BLOCK_SIZE_SMALL + (i + 1)*NEW_FIGURE_WIDTH;
		currentY = PLAYING_FIELD;
	}
}

int PlayingField::SearchMaxCloseValue(int sourceValue,int startPoint)
{
	int resultValue = startPoint;
	for (int i = 0; i < BLOCKS_COUNT;i++)
		if (resultValue < sourceValue)
			resultValue += BLOCK_SIZE;
		else
		{
			if (resultValue != BLOCK_SIZE && resultValue != FIELD_START)
				resultValue -= BLOCK_SIZE;
			break;
		}
		if (resultValue == PLAYING_FIELD || resultValue == BLOCK_SIZE*(BLOCKS_COUNT + 1))
			resultValue -= BLOCK_SIZE;
	return resultValue;
}

int PlayingField::GetRectArea(RECT rect)
{
	return (rect.right - rect.left)*(rect.bottom - rect.top);
}

int PlayingField::SearchStartBlockNumberForChooseFigure(RECT startFigureBlockRect,RECT figureRect,int row, int column)
{
	int blockNumber = 0,resultRectangleArea=0;
	RECT currentFieldRect;
	for (int i = row; (i < row+2) && (i<BLOCKS_COUNT); i++)
		for (int j = column; (j < column + 2) && (j<BLOCKS_COUNT); j++)
		if (IntersectRect(&currentFieldRect, &(blocks[i][j].GetFieldBlockRect()), &startFigureBlockRect))
		{
			int currentRectArea = GetRectArea(currentFieldRect);
			if (resultRectangleArea < currentRectArea)
			{
				resultRectangleArea = currentRectArea;
				blockNumber = i*BLOCKS_COUNT + j;
				if (figureRect.right>fieldRect.right)
					break;
			}
		}
	return blockNumber;
}

int PlayingField::GetStartBlockNumberForChooseFigure(RECT figureRect,int x,int y)
{
	RECT startFigureBlockRect = { figureRect.left, figureRect.bottom - BLOCK_SIZE, figureRect.left + BLOCK_SIZE, figureRect.bottom };
	int currentX = SearchMaxCloseValue(startFigureBlockRect.left, fieldRect.left), currentY = SearchMaxCloseValue(startFigureBlockRect.top, fieldRect.top);
	int blockNumber = SearchStartBlockNumberForChooseFigure(startFigureBlockRect, figureRect, (currentY - fieldRect.top) / BLOCK_SIZE, (currentX - fieldRect.left) / BLOCK_SIZE);
	return blockNumber;
}

void PlayingField::TrySetChoosingFigure(int x, int y)
{
	if (chooseFigure != NULL)
	{
		int blockNumber = 0,setBlockCount=0;
		if (chooseFigure->CheckPlaceForFigure(fieldRect))
		{
			blockNumber = GetStartBlockNumberForChooseFigure(chooseFigure->GetFigureRect(), x, y);
			if (setBlockCount=chooseFigure->SetFigureOnChoosePlace(blockTable, blockNumber))
			{
				setBlockCount += SearchFullRows() + SearchFullColumns();
				RemoveFigure();
				if (figures.empty())
					fieldState = CREATE;
			}
		}
		chooseFigure->SetRectStartPoint(oldFigureStartPoint.x, oldFigureStartPoint.y);
		oldFigureStartPoint.x = 0;
		oldFigureStartPoint.y = 0;
		chooseFigure = NULL;
	}
}

void PlayingField::UpdatePlayingField(HDC hdc,int x,int y)
{
	HPEN oldPen = SelectPen(hdc, hPen);
	switch (fieldState)
	{
		case CREATE:
			PaintPlayingField(hdc);
			CreateNewFigures(hdc);
			fieldState = REPAINT;
			break;
		case REPAINT:
			PaintPlayingField(hdc);
			RepaintOtherFigures(hdc);
			RepaintChooseFigure(hdc, x, y);
			break;
		default:
			break;
	}
	SelectPen(hdc, oldPen);
}