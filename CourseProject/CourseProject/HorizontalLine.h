#pragma once
class HorizontalLine :public Figure
{
	public:
		HorizontalLine();
		HorizontalLine(int);
		~HorizontalLine();
		void DrawFigure(HDC,int,int,int);
		int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

