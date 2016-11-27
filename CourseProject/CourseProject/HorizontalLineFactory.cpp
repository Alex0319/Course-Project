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
