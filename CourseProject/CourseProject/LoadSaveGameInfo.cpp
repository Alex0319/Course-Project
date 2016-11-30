#include "stdafx.h"
#include "LoadSaveGameInfo.h"


LoadSaveGameInfo::LoadSaveGameInfo()
{
}


LoadSaveGameInfo::~LoadSaveGameInfo()
{
}

void LoadSaveGameInfo::SetFigureIndex(int value)
{
	figureIndices.push_back(value);
}

void LoadSaveGameInfo::ClearFigureIndex(int index)
{
	figureIndices.erase(figureIndices.begin()+index);
	if (!figureIndices.empty())
		std::vector<int>(figureIndices).swap(figureIndices);
}

void LoadSaveGameInfo::Clear()
{
	figureIndices.clear();
	std::vector<int>().swap(figureIndices);
}

int LoadSaveGameInfo::LoadGameRecord()
{
	int result = 0;
	std::ifstream infile(recordInfoFilename, std::ios::binary | std::ios::in);
	if (infile.is_open())
	{
		infile.read((char*)&result, sizeof result);
		infile.close();
	}
	return result;
}

void LoadSaveGameInfo::SaveGameRecord(int record)
{
	std::ofstream outfile(recordInfoFilename, std::ios::binary | std::ios::out);
	outfile.write((char*)&record, sizeof record);
	outfile.close();
}

void LoadSaveGameInfo::SaveGameInfo(BlockColors(*blockTable)[BLOCKS_COUNT], std::vector<Figure*>& figures,int currentScore)
{
	std::ofstream outfile(filename, std::ios::binary | std::ios::out);
	for (int i = 0; i < BLOCKS_COUNT; i++)
		for (int j = 0; j < BLOCKS_COUNT; j++)
			outfile.write((char*)&blockTable[i][j], sizeof blockTable[i][j]);
	outfile.write((char*)&currentScore, sizeof currentScore);
	for (int i = 0; i < figures.size(); i++)
	{
		std::string figurePropertiesStr = figures[i]->GetFigureProperties();
		int length = strlen(figurePropertiesStr.c_str());
		outfile.write((char*)&figureIndices[i],sizeof figureIndices[i]);
		outfile.write((char*)&length, sizeof length);
		outfile.write((char*)figurePropertiesStr.c_str(), length);
	}
	outfile.close();
}

int LoadSaveGameInfo::TryLoadGameInfo(BlockColors(*blockTable)[BLOCKS_COUNT], std::vector<Figure*>& figures, std::vector<FigureFactory*> factory, LoadSaveGameInfo* gameInfo,int* currentScore)
{
	int result = 0;
	std::ifstream infile(filename, std::ios::binary | std::ios::in);
	if (infile.is_open())
	{
		BlockColors currentBlockColor;
		for (int i = 0; i < BLOCKS_COUNT; i++)
			for (int j = 0; j < BLOCKS_COUNT; j++)
			{
				infile.read((char*)&currentBlockColor, sizeof currentBlockColor);
				if (currentBlockColor != DEFAULT)
					result++;
				blockTable[i][j] = currentBlockColor;
			}
		infile.read((char*)currentScore, sizeof *currentScore);
		while (!infile.eof())
		{
			size_t size;
			int factoryIndex = 0;
			infile.read((char*)&factoryIndex, sizeof factoryIndex);
			infile.read((char*)&size, sizeof size);
			char* buffer = (char*)malloc((size + 1)*sizeof(char));
			if (buffer != NULL)
			{
				ZeroMemory(buffer, sizeof buffer);
				infile.read(buffer, size);
				if (strlen(buffer) != 0)
				{
					Figure* resultFigure = factory[factoryIndex]->CreateFigure(std::string(buffer));
					gameInfo->SetFigureIndex(factoryIndex);
					figures.push_back(resultFigure);
				}
				free(buffer);
			}
		}
		infile.close();
	}
	return result;
}
