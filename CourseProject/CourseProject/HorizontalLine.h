#pragma once
class HorizontalLine :public Figure
{
	public:
		HorizontalLine();
		HorizontalLine(std::string);
		~HorizontalLine();
		void DrawFigure(HDC,int,int,int);
		int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int);
		bool CheckBlock(BlockColors(*)[BLOCKS_COUNT], int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

