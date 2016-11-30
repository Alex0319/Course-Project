#include "stdafx.h"

VerticalLineFactory::VerticalLineFactory()
{
}


VerticalLineFactory::~VerticalLineFactory()
{
}

Figure* VerticalLineFactory::CreateFigure()
{
	return new VerticalLine();
}

Figure* VerticalLineFactory::CreateFigure(std::string figureProperties)
{
	return new VerticalLine(figureProperties);
}
