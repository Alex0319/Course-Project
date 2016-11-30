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

Figure* SquareFactory::CreateFigure(std::string figureProperties)
{
	return new Square(figureProperties);
}