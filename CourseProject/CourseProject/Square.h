#pragma once
class Square :	public Figure
{
	public:
		Square();
		~Square();
		void DrawFigure(HDC,int,int,int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

