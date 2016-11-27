#pragma once
class FigureFactory
{
	public:
		FigureFactory();
		~FigureFactory();
		virtual Figure* CreateFigure()=0;
};

