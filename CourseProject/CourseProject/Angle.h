#pragma once
class Angle : public Figure
{
	public:
		Angle();
		Angle(std::string);
		~Angle();
		void DrawFigure(HDC, int, int,int);
		int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int);
		bool CheckBlock(BlockColors(*)[BLOCKS_COUNT], int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
		std::string GetFigureProperties();
	protected:
		bool Check(BlockColors(*)[BLOCKS_COUNT], int, int, int, int);
		int SetFigure(BlockColors(*)[BLOCKS_COUNT], int, int, int, int);
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
		bool CheckBlocks(BlockColors(*)[BLOCKS_COUNT], int*,int, int,bool);
		void SetBlockColors(BlockColors(*)[BLOCKS_COUNT], int*, int, int, bool);
};
