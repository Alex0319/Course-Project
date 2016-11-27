#include "stdafx.h"

SquareFactory::SquareFactory()
{
}

SquareFactory::~SquareFactory()
{
}

Figure* SquareFactory::CreateFigure()
{
	return new Square();
}
