#pragma once
class Block
{
	public:
		Block();
		~Block();
		void DrawBlock(HDC, COLORREF,int,int,int);
	protected:
		const int ellipseSize = 8;
		HBRUSH hBrush;
};

