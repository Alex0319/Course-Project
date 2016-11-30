#pragma once
class FigureFactory
{
	public:
		FigureFactory();
		~FigureFactory();
		virtual Figure* CreateFigure()=0;
		virtual Figure* CreateFigure(std::string) = 0;
};

