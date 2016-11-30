#include "stdafx.h"

PlayingField::PlayingField()
{
	gameRecord = gameInfo.LoadGameRecord();
	figureFactories.push_back(new SquareFactory);
	figureFactories.push_back(new HorizontalLineFactory);
	figureFactories.push_back(new VerticalLineFactory);
	figureFactories.push_back(new AngleFactory);
	fieldRect = { BLOCK_SIZE, FIELD_START, BLOCK_SIZE*(BLOCKS_COUNT + 1), PLAYING_FIELD };
	hPen = GetStockPen(NULL_PEN);
	if (!(currentNumberOfOccupiedBlocks = gameInfo.TryLoadGameInfo(blockTable,figures,figureFactories,&gameInfo,&currentScore)))
		InitializeNewGame();
	else
		fieldState = DRAWSAVED;
}

PlayingField::~PlayingField()
{
	DeleteObject(hPen);
	gameInfo.SaveGameInfo(blockTable, figures,currentScore);
	gameInfo.SaveGameRecord(gameRecord);
	ClearFiguresVector();
	for (auto it = figureFactories.begin(); it != figureFactories.end();it++)
		delete *it;
	figureFactories.clear();
}

void PlayingField::InitializeNewGame()
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
		for (int j = 0; j < BLOCKS_COUNT; j++)
			blockTable[i][j] = DEFAULT;
	fieldState = CREATE;
	currentNumberOfOccupiedBlocks = currentScore = 0;
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
				blockTable[i][j] = DELETECOLOR;
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
		if (i == BLOCKS_COUNT)
		{
			for (i = 0; i < BLOCKS_COUNT; i++)
				blockTable[i][j] = DELETECOLOR;
			blocksCount += BLOCKS_COUNT;
		}
	}
	return blocksCount;
}

int PlayingField::ClearFullRowsAndColumns()
{
	int result = SearchFullRows() + SearchFullColumns();
	for (int i = 0; i < BLOCKS_COUNT; i++)
		for (int j = 0; j < BLOCKS_COUNT; j++)
			if (blockTable[i][j] == DELETECOLOR)
				blockTable[i][j] = DEFAULT;
	return result;
}

bool PlayingField::CheckEmptyCells()
{
	if (currentNumberOfOccupiedBlocks<BLOCKS_COUNT*BLOCKS_COUNT / 4)
		return true;
	if (figures.empty())
		CreateNewFigures();
	for (int i = 0; i < BLOCKS_COUNT;i++)
		for (int j = 0; j < BLOCKS_COUNT; j++)
			if (blockTable[i][j]==DEFAULT)
				for (auto k = 0; k < figures.size();k++)
					if (figures[k]->CheckBlock(blockTable, i*BLOCKS_COUNT + j))
						return true;
	return false;
}

void PlayingField::UpdateGameValues(int countOfSetBlocks, int countOfFreedBlocks)
{
	currentScore += countOfSetBlocks + countOfFreedBlocks;
	currentNumberOfOccupiedBlocks += countOfSetBlocks - countOfFreedBlocks;
}

int PlayingField::GetCurrentScore()
{
	return currentScore;
}

int PlayingField::GetGameRecord()
{
	if (gameRecord < currentScore)
		gameRecord = currentScore;
	return gameRecord;
}

void PlayingField::ClearFiguresVector()
{
	for (auto it = figures.begin(); it != figures.end(); it++)
		delete *it;
	if (!figures.empty())
		std::vector<Figure*>().swap(figures);
	gameInfo.Clear();
	oldFigureStartPoint.x = 0;
	oldFigureStartPoint.y = 0;
}

void PlayingField::RemoveFigure()
{
	for (auto i = 0; i < figures.size();i++)
		if (chooseFigure == figures[i])
		{
			figures.erase(figures.begin() + i);
			if (!figures.empty())
				std::vector<Figure*>(figures).swap(figures);
			gameInfo.ClearFigureIndex(i);
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
	for (auto i = 0; i < figures.size(); i++)
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
	for (auto i=0; i<figures.size(); i++)
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

void PlayingField::CreateNewFigures()
{
	srand(time(0));
	ClearFiguresVector();
	int currentX = BLOCK_SIZE_SMALL, currentY = PLAYING_FIELD;
	for (int i = 0; i < NEW_FIGURES_COUNT; i++)
	{
		int figureIndex = rand() % figureFactories.size();
		figures.push_back(figureFactories[figureIndex]->CreateFigure());
		gameInfo.SetFigureIndex(figureIndex);
		currentX += (NEW_FIGURE_WIDTH - BLOCK_SIZE_SMALL*figures.back()->GetBlocksCountInRow()) / 2;
		currentY += (NEW_FIGURE_HEIGHT - BLOCK_SIZE_SMALL*figures.back()->GetBlocksCountInColumn()) / 4;
		figures.back()->SetRectStartPoint(currentX, currentY);
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

int PlayingField::GetStartBlockNumberForChooseFigure(RECT figureRect)
{
	RECT startFigureBlockRect = { figureRect.left, figureRect.bottom - BLOCK_SIZE, figureRect.left + BLOCK_SIZE, figureRect.bottom };
	int currentX = SearchMaxCloseValue(startFigureBlockRect.left, fieldRect.left), currentY = SearchMaxCloseValue(startFigureBlockRect.top, fieldRect.top);
	int blockNumber = SearchStartBlockNumberForChooseFigure(startFigureBlockRect, figureRect, (currentY - fieldRect.top) / BLOCK_SIZE, (currentX - fieldRect.left) / BLOCK_SIZE);
	return blockNumber;
}

bool PlayingField::TrySetChoosingFigure()
{
	if (chooseFigure != NULL)
	{
		int blockNumber = 0,setBlockCount=0;
		if (chooseFigure->CheckPlaceForFigure(fieldRect))
		{
			blockNumber = GetStartBlockNumberForChooseFigure(chooseFigure->GetFigureRect());
			if (setBlockCount = chooseFigure->SetFigureOnChoosePlace(blockTable, blockNumber))
			{
				UpdateGameValues(setBlockCount, ClearFullRowsAndColumns());
				RemoveFigure();
				delete chooseFigure;
				chooseFigure = NULL;
				if (!CheckEmptyCells())
					return false;
				if (figures.empty())
					fieldState = CREATE;
			}
		}
		if (chooseFigure != NULL)
		{
			chooseFigure->SetRectStartPoint(oldFigureStartPoint.x, oldFigureStartPoint.y);
			chooseFigure = NULL;
		}
		oldFigureStartPoint.x = 0;
		oldFigureStartPoint.y = 0;
	}
	return true;
}

void PlayingField::UpdatePlayingField(HDC hdc,int x,int y)
{
	HPEN oldPen = SelectPen(hdc, hPen);
	PaintPlayingField(hdc);
	switch (fieldState)
	{
		case CREATE: 
			CreateNewFigures();
			RepaintOtherFigures(hdc);
			break;
		case REPAINT:
			RepaintOtherFigures(hdc);
			RepaintChooseFigure(hdc, x, y);
			break;
		case DRAWSAVED:	RepaintOtherFigures(hdc);
			break;
		default:
			break;
	}
	fieldState = REPAINT;
	SelectPen(hdc, oldPen);
}
