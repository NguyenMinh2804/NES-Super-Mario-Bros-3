#pragma once
#include <unordered_map>
#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx10.h"

#include "Texture.h"

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures* __instance;

	unordered_map<int, LPTEXTURE> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath);
	LPTEXTURE Get(unsigned int i);
	void Clear();

	static CTextures* GetInstance();
};