#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Map.h"
#include "Turtle.h"
//#include "Koopas.h"

#define INTRO_SCREEN_ID 8
#define WORLD_1_ID 7
#define WORLD_1_1_ID 6


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	int gameTime;
	void _ParseSection_MAPS(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line, int objId);

	void LoadAssets(LPCWSTR assetFile);
	
public:
	LPGAMEOBJECT intro;
	Map* map = NULL;
	CPlayScene(int id, LPCWSTR filePath);
	vector<LPGAMEOBJECT> objects;
	vector<CTurtle> reSurrectionObjects;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void AddObject(CGameObject *object);
	bool LinearSearch(int x);
	bool isInExtraMap = false;
};

typedef CPlayScene* LPPLAYSCENE;

