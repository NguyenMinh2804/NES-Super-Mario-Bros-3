#include <fstream>
#include <iostream>
#include "Map.h"
#include"Utils.h"
#include "AssetIDs.h"
#include "debug.h"

Map::Map(int idMap, int nTitleCols, int nTitleRows, int nMapCols,
	int nMapRows, int nTotalTiles)
{
	this->tileSet = CTextures::GetInstance()->Get(idMap);

	this->totalRowsOfMap = nMapCols;
	this->totalColsOfMap = nMapRows;

	this->totalRowsOfTileSet = nTitleRows;
	this->totalColsOfTitleSet = nTitleCols;

	this->totalTiles = nTotalTiles;
}
Map::~Map()
{

}
void Map::CreateTilesFromTileSet()
{
	int left, bottom, right, top;
	for (int tileNum = 0; tileNum < totalTiles; tileNum++) {
		left = tileNum % totalColsOfTitleSet * TILE_WIDTH;
		top = tileNum / totalColsOfTitleSet * TILE_HEIGHT;
		bottom = top + TILE_HEIGHT;
		right = left + TILE_WIDTH;
		LPSPRITE Tile = new CSprite(tileNum, left, top,
			right, bottom, tileSet);
		this->tiles.push_back(Tile);
	}
}
void Map::LoadMatrix(LPCWSTR path)
{
	ifstream file;

	file.open(path);
	this->matrix = new int* [totalColsOfMap];
	for (int iRow = 0; iRow < totalColsOfMap; iRow++)
	{
		this->matrix[iRow] = new int[totalRowsOfMap];
		for (int iColumn = 0; iColumn < totalRowsOfMap; iColumn++)
		{
			file >> this->matrix[iRow][iColumn];
		}

	}
	file.close();
}
void Map::Render(float l, float t, float r, float b)
{

	int LastColumn = totalRowsOfMap;
	int LastRow = totalColsOfMap;
	for (int iRow = 0; iRow < LastRow; iRow++)
	{
		for (int iColumn = 0; iColumn < LastColumn; iColumn++)
		{
			if (this->matrix[iRow][iColumn] == 0)
			{
				continue;
			}
			float x, y;
			x = (float)iColumn * TILE_WIDTH;
			y = (float)iRow * TILE_HEIGHT;
			float tileL = x;
			float tileT = y;
			float tileR = l + 16;
			float tileB = t + 16;
			if (tileL < r + 8 && tileR > l && tileT < b + 8 && tileB > t)
			{
				this->tiles[this->matrix[iRow][iColumn] - 1]->Draw(x, y);			
			}
		}
	}
}
int Map::GetMapHeiht()
{
	if (height == 0)
		height = totalColsOfMap * TILE_HEIGHT;
	return height;
}
int Map::GetMapWidth()
{
	if (width == 0)
	{
		width = totalRowsOfMap * TILE_WIDTH;
	}
	return width;
}
void Map::LoadInformation(LPCWSTR path)
{
	ifstream f;
	f.open(path);
	if (!f)
		DebugOut(L"\nFailed to open file!");
	char str[MAX_SCENE_LINE];
	f.getline(str, MAX_SCENE_LINE);
	string line(str);

	vector<string> tokens = split(line);
	if (tokens.size() < 6) return; // skip invalid lines

	int idMap = atoi(tokens[0].c_str());
	int tolRowTileSet = atoi(tokens[1].c_str());
	int tolColTileSet = atoi(tokens[2].c_str());
	int tolRowMap = atoi(tokens[3].c_str());
	int tolColMap = atoi(tokens[4].c_str());
	int totalTiles = atoi(tokens[5].c_str());
	this->Init(idMap, tolRowTileSet, tolColTileSet,
		tolRowMap, tolColMap, totalTiles);
}


void Map::Init(int idMap, int nTitleCols, int nTitleRows, int nMapCols,
	int nMapRows, int nTotalTiles)
{
	this->tileSet = CTextures::GetInstance()->Get(idMap);

	this->totalRowsOfMap = nMapCols;
	this->totalColsOfMap = nMapRows;

	this->totalRowsOfTileSet = nTitleRows;
	this->totalColsOfTitleSet = nTitleCols;

	this->totalTiles = nTotalTiles;
}