#pragma once

#include <vector>

class PlayingField
{
	public:
		PlayingField();
		~PlayingField();
		void UpdatePlayingField(HDC,int,int);
		void TrySetChoosingFigure(int, int);
		bool CheckClientClick(POINT);
		bool CheckFigureChoose();
	private:
		const int newFiguresCount = 3;
		RECT fieldRect;
		POINT oldFigureStartPoint;
		HPEN hPen;
		enum FieldState
		{
			CREATE,
			REPAINT
		} fieldState;
		Figure* chooseFigure;
		FieldBlock blocks[BLOCKS_COUNT][BLOCKS_COUNT];
		BlockColors blockTable[BLOCKS_COUNT][BLOCKS_COUNT];
		std::vector<Figure*> figures;
		std::vector<FigureFactory*> figureFactories;
		void PaintPlayingField(HDC);
		void CreateNewFigures(HDC);
		void RepaintChooseFigure(HDC,int,int);
		void RepaintOtherFigures(HDC);
		int GetRectArea(RECT);
		int GetStartBlockNumberForChooseFigure(RECT,int,int);
		int SearchStartBlockNumberForChooseFigure(RECT,RECT,int, int);
		int SearchMaxCloseValue(int,int);
		int SearchFullRows();
		int SearchFullColumns();
		void ClearFiguresVector();
		void RemoveFigure();
};
