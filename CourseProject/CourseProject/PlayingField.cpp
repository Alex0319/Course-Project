#include "stdafx.h"

PlayingField::PlayingField()
{
	fieldState = CREATE;
	figureFactories.push_back(new SquareFactory);
	figureFactories.push_back(new HorizontalLineFactory);
	figureFactories.push_back(new VerticalLineFactory);
	figureFactories.push_back(new AngleFactory);
	fieldRect = { BLOCK_SIZE, WINDOW_HEIGHT / 8, BLOCK_SIZE*(BLOCKS_COUNT + 1), PLAYING_FIELD };
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

void PlayingField::TrySetChoosingFigure(int x, int y)
{
	if (chooseFigure != NULL)
	{
		if (chooseFigure->CheckPlaceForFigure(fieldRect))
		{
			
			RemoveFigure();
			if (figures.size()==0)
				fieldState = CREATE;
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