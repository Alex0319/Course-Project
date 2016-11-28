#pragma once
class Figure
{
	public:
		Figure();
		~Figure();
		virtual void DrawFigure(HDC,int,int,int)=0;
		virtual int GetBlocksCountInColumn()=0;
		virtual int GetBlocksCountInRow() = 0;
		RECT GetFigureRect();
		bool CheckPlaceForFigure(RECT);
		void SetRectStartPoint(int, int);
protected:
		COLORREF figureColor;
		int blocksCount;
		Block figureBlock;
		RECT figureRect;
		void SetRectEndPoint(int, int);
};

