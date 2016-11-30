#pragma once
class Figure
{
	public:
		Figure();
		Figure(std::string);
		~Figure();
		virtual void DrawFigure(HDC,int,int,int)=0;
		virtual int GetBlocksCountInColumn()=0;
		virtual int GetBlocksCountInRow() = 0;
		virtual int SetFigureOnChoosePlace(BlockColors(*)[BLOCKS_COUNT], int)=0;
		virtual bool CheckBlock(BlockColors(*)[BLOCKS_COUNT], int)=0;
		virtual std::string GetFigureProperties();
		RECT GetFigureRect();
		bool CheckPlaceForFigure(RECT);
		void SetRectStartPoint(int, int);
	protected:
		BlockColors figureColor;
		int blocksCount;
		Block figureBlock;
		RECT figureRect;
		virtual bool Check(BlockColors(*)[BLOCKS_COUNT], int, int, int,int);
		virtual int SetFigure(BlockColors(*)[BLOCKS_COUNT], int, int, int,int);
		void SetRectEndPoint(int, int);
	private:
		bool CheckResultRect(RECT, RECT);
};
