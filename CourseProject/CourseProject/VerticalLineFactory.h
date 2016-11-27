#pragma once
class VerticalLineFactory : public FigureFactory
{
	public:
		VerticalLineFactory();
		~VerticalLineFactory();
		Figure* CreateFigure();
};

