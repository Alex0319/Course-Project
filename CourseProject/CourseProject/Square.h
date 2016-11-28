#pragma once
class Square :	public Figure
{
	public:
		Square();
		~Square();
		void DrawFigure(HDC,int,int,int);
		int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

