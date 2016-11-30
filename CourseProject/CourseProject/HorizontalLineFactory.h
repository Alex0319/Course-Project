#pragma once

class HorizontalLineFactory :	public FigureFactory
{
	public:
		HorizontalLineFactory();
		~HorizontalLineFactory();
		Figure* CreateFigure(std::string);
		Figure* CreateFigure();
};

