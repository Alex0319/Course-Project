#pragma once
class VerticalLine : public Figure
{
	public:
		VerticalLine();
		~VerticalLine();
		void DrawFigure(HDC, int, int,int);
		int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

