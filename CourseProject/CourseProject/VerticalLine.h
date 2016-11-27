#pragma once
#include "Figure.h"
class VerticalLine : public Figure
{
	public:
		VerticalLine();
		~VerticalLine();
		void DrawFigure(HDC, int, int,int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

