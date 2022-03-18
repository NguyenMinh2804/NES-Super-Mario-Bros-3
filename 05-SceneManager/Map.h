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

	Map(int idMap, int nTitleCols,
		int nTitleRows, int nMapCols, int nMapRows,
		int nTotalTiles);
	~Map();
	Map() {};
	void Init(int idMap, int nTitleCols,
		int nTitleRows, int nMapCols, int nMapRows,
		int nTotalTiles);
	void CreateTilesFromTileSet();
	void LoadMatrix(LPCWSTR path);
	void LoadInformation(LPCWSTR path);
	void Render();
	int GetTotalColsOfMap() { return this->totalRowsOfMap; }
	int GetTotalRowsOfMap() { return this->totalColsOfMap; }
	int GetMapHeiht();
	int GetMapWidth();
};
