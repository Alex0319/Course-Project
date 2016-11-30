#pragma once
#include "stdafx.h"
#include "CourseProject.h"
#include "Figure.h"
#include "FigureFactory.h"

class LoadSaveGameInfo
{
	public:
		LoadSaveGameInfo();
		~LoadSaveGameInfo();
		void SaveGameInfo(BlockColors(*)[BLOCKS_COUNT], std::vector<Figure*>&,int);
		int TryLoadGameInfo(BlockColors(*)[BLOCKS_COUNT], std::vector<Figure*>&, std::vector<FigureFactory*>,LoadSaveGameInfo*,int*);
		int LoadGameRecord();
		void SaveGameRecord(int);
		void SetFigureIndex(int);
		void ClearFigureIndex(int);
		void Clear();
	private:
		char* filename = "GameInfo.txt";
		char* recordInfoFilename = "Record.txt";
		std::vector<int> figureIndices;
};

