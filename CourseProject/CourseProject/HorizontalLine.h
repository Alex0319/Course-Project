#pragma once
class HorizontalLine :public Figure
{
	public:
		HorizontalLine();
		HorizontalLine(int);
		~HorizontalLine();
		void DrawFigure(HDC,int,int,int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

