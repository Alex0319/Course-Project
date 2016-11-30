#include "stdafx.h"

HorizontalLineFactory::HorizontalLineFactory()
{
}


HorizontalLineFactory::~HorizontalLineFactory()
{
}

Figure* HorizontalLineFactory::CreateFigure()
{
	return new HorizontalLine();
}

Figure* HorizontalLineFactory::CreateFigure(std::string figureProperties)
{
	return new HorizontalLine(figureProperties);
}