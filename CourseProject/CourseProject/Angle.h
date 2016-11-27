#pragma once
class Angle : public Figure
{
	public:
		Angle();
		~Angle();
		void DrawFigure(HDC, int, int,int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
	private:
		enum AngleType
		{
			LEFTTOP = 1,
			LEFTBOTTOM,
			RIGHTTOP,
			RIGHTBOTTOM
		} angleType;
		int blocksCountInColumn;
		void DrawLine(HDC, int, int,int,int);
		void DrawColumn(HDC, int, int, int,int);
};
