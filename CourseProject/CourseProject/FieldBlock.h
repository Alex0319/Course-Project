#pragma once
class FieldBlock :	public Block
{
	public:
		FieldBlock();
		~FieldBlock();
		void DrawBlock(HDC, COLORREF, int, int, int);
		RECT GetFieldBlockRect();
	private:
		RECT blockRect;
		void SetBlockRect(int, int);
};

