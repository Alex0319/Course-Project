#include "stdafx.h"

AngleFactory::AngleFactory()
{
}


AngleFactory::~AngleFactory()
{
}

Figure* AngleFactory::CreateFigure()
{
	return new Angle();
}
