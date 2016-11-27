#pragma once
class HorizontalLineFactory :	public FigureFactory
{
	public:
		HorizontalLineFactory();
		~HorizontalLineFactory();
		Figure* CreateFigure();
};

