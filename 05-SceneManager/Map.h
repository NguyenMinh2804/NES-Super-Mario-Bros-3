#pragma once
#include"Textures.h"
#include "Sprites.h"
#include <d3d10.h>

class Map
{
	int** matrix;
	int totalColsOfTitleSet, totalRowsOfTileSet;
	int totalRowsOfMap, totalColsOfMap;
	int totalTiles;


	LPTEXTURE tileSet;
	vector<LPSPRITE> tiles;
	int height = 0;
	int width = 0;



public:
	int maxX;
	int maxY;
	int minY;
	Map(int idMap, int nTitleCols,
		int nTitleRows, int nMapCols, int nMapRows,
		int nTotalTiles);
	~Map();
	Map() {};
	void Init(int idMap, int nTitleCols,
		int nTitleRows, int nMapCols, int nMapRows,
		int nTotalTiles, int maxX, int maxY, int minY);
	void CreateTilesFromTileSet();
	void LoadMatrix(LPCWSTR path);
	void LoadInformation(LPCWSTR path);
	void Render(float l, float t, float r, float b);
	int GetTotalColsOfMap() { return this->totalRowsOfMap; }
	int GetTotalRowsOfMap() { return this->totalColsOfMap; }
	int GetMapHeiht();
	int GetMapWidth();
};
