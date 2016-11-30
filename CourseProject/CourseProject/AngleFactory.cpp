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

Figure* AngleFactory::CreateFigure(std::string figureProperties)
{
	return new Angle(figureProperties);
}
