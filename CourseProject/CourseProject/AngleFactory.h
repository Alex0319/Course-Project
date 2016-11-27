#pragma once
class AngleFactory : public FigureFactory
{
	public:
		AngleFactory();
		~AngleFactory();
		Figure* CreateFigure();
};

