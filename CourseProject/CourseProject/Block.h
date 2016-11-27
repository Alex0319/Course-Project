#pragma once
class Block
{
	public:
		Block();
		~Block();
		void DrawBlock(HDC, COLORREF,int,int,int);
	private:
		const int ellipseSize = 8;
		HBRUSH hBrush;

};

