#pragma once

#include <vector>

class PlayingField
{
	public:
		PlayingField();
		~PlayingField();
		void UpdatePlayingField(HDC,int,int);
		bool CheckClientClick(POINT);
		bool CheckFigureChoose();
	private:
		const int newFiguresCount = 3;
		HPEN hPen;
		enum FieldState
		{
			CREATE,
			REPAINT
		} fieldState;
		Figure* chooseFigure;
		Block blocks[BLOCKS_COUNT][BLOCKS_COUNT];
		BlockColors blockTable[BLOCKS_COUNT][BLOCKS_COUNT];
		std::vector<Figure*> figures;
		std::vector<FigureFactory*> figureFactories;
		void PaintPlayingField(HDC);
		void CreateNewFigures(HDC);
		void RepaintChooseFigure(HDC,int,int);
		void RepaintOtherFigures(HDC);
		void ClearFiguresVector();
};
