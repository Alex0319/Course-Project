#pragma once

class AngleFactory : public FigureFactory
{
	public:
		AngleFactory();
		~AngleFactory();
		Figure* CreateFigure();
		Figure* CreateFigure(std::string);
};

