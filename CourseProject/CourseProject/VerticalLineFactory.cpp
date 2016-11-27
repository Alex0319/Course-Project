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
