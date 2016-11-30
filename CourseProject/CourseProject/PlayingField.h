#pragma once

#include "LoadSaveGameInfo.h"

class PlayingField
{
	public:
		PlayingField();
		~PlayingField();
		void UpdatePlayingField(HDC,int,int);
		void InitializeNewGame();
		bool TrySetChoosingFigure();
		bool CheckClientClick(POINT);
		bool CheckFigureChoose();
		int GetGameRecord();
		int GetCurrentScore();
	private:
		RECT fieldRect;
		POINT oldFigureStartPoint;
		HPEN hPen;
		int currentNumberOfOccupiedBlocks = 0, currentScore = 0,gameRecord=0;
		enum FieldState
		{
			CREATE,
			REPAINT,
			DRAWSAVED
		} fieldState;
		LoadSaveGameInfo gameInfo;
		Figure* chooseFigure;
		FieldBlock blocks[BLOCKS_COUNT][BLOCKS_COUNT];
		BlockColors blockTable[BLOCKS_COUNT][BLOCKS_COUNT];
		std::vector<Figure*> figures;
		std::vector<FigureFactory*> figureFactories;
		void PaintPlayingField(HDC);
		void RepaintChooseFigure(HDC,int,int);
		void RepaintOtherFigures(HDC);
		void CreateNewFigures();
		int GetRectArea(RECT);
		int GetStartBlockNumberForChooseFigure(RECT);
		int SearchStartBlockNumberForChooseFigure(RECT,RECT,int, int);
		int SearchMaxCloseValue(int,int);
		int SearchFullRows();
		int SearchFullColumns();
		int ClearFullRowsAndColumns();
		void ClearFiguresVector();
		void RemoveFigure();
		void UpdateGameValues(int, int);
		bool CheckEmptyCells();
};
