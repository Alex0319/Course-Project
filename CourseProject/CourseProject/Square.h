#pragma once
class Square :	public Figure
{
	public:
		Square();
		Square(std::string);
		~Square();
		void DrawFigure(HDC,int,int,int);
		int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int);
		bool CheckBlock(BlockColors(*)[BLOCKS_COUNT], int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

