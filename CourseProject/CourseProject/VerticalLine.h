#pragma oncez
class VerticalLine : public Figure
{
	public:
		VerticalLine();
		VerticalLine(std::string);
		~VerticalLine();
		void DrawFigure(HDC, int, int,int);
		int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int);
		bool CheckBlock(BlockColors(*)[BLOCKS_COUNT], int);
		int GetBlocksCountInColumn();
		int GetBlocksCountInRow();
};

