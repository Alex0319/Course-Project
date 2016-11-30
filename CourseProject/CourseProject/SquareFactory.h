#pragma once
class SquareFactory : public FigureFactory
{
	public:
		SquareFactory();
		~SquareFactory();
		Figure* CreateFigure();
		Figure* CreateFigure(std::string);
};

