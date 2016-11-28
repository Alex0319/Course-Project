#include "stdafx.h"

Figure::Figure()
{
}

Figure::~Figure()
{
}

void Figure::SetRectStartPoint(int x, int y)
{
	figureRect.left = x;
	figureRect.top = y;
}

void Figure::SetRectEndPoint(int x, int y)
{
	if (x != 0)
		figureRect.right = x;
	if (y != 0)
		figureRect.bottom = y;
}

RECT Figure::GetFigureRect()
{
	return figureRect;
}

bool Figure::CheckPlaceForFigure(RECT fieldRect)
{
	RECT resultRect;
	if (!IntersectRect(&resultRect, &fieldRect, &figureRect))
		return false;
}