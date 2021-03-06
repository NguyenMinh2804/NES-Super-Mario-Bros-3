#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Ground.h"
#include "Rectangle.h"
#include "Platform.h"
#include "Wood.h"
#include "WaterPipe.h"
#include "FlowerFire.h"
#include "Fire.h"
#include "BrickQuestion.h"
#include "Brick2.h"
#include "Map.h"
#include "SampleKeyEventHandler.h"
#include "World1KeyHandleEvent.h"
#include "Mushroom.h"
#include "FlyGoomba.h"
#include "InvisibleWall.h"
#include "Wall.h"
#include "Turtle.h"
#include "Teleport.h"
#include "Tree.h"
#include "Camel.h"
#include "IntroKeyHandleEvent.h"
#include "Intro.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_MAPS	3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	if (id == WORLD_1_ID)
	{
		key_handler = new CWorld1KeyHandleEvent(this);
	}
	else if (id == WORLD_1_1_ID)
	{
		key_handler = new CSampleKeyHandler(this);
	}
	else if(id == INTRO_SCREEN_ID)
	{
		key_handler = new CIntroKeyHandleEvent(this);
	}
}


void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line, int objId)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y, gameTime);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_FLYGOOMBA: obj = new CFlyGoomba(x, y); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_BRICK2:
	{
		float type = (float)atof(tokens[3].c_str());
		obj = new CBrick2(x, y, type); break;
	}
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y, 0); break;
	case OBJECT_TYPE_GROUND:
	{
		float type = (float)atof(tokens[3].c_str());
		obj = new CGround(x, y, type); break;
	}
	case OBJECT_TYPE_RECTANGLE:
	{
		float type = (float)atof(tokens[3].c_str());
		float size = (float)atof(tokens[4].c_str());
		obj = new CRectangle(x, y, type, size); break;
	}
	case OBJECT_TYPE_WOOD:
	{
		float type = (float)atof(tokens[3].c_str());
		obj = new CWood(x, y, type); break;
	}
	case OBJECT_TYPE_WATER_PIPE:
	{
		float size = (float)atof(tokens[3].c_str());
		float type = (float)atof(tokens[4].c_str());
		obj = new CWaterPipe(x, y, size, type); break;
	}
	case OBJECT_TYPE_FLOWER_FIRE:
	{
		float type = (float)atof(tokens[3].c_str());
		obj = new CFlowerFire(x, y, type); break;
	}
	case OBJECT_TYPE_BRICK_QUESTION:
	{
		float type = (float)atof(tokens[3].c_str());
		obj = new CBrickQuestion(x, y, type); break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	case OBJECT_TYPE_INVISIBLEWALL:
	{
		obj = new CInvisibleWall(x, y);
		break;
	}
	case OBJECT_TYPE_WALL:
	{
		obj = new CWall(x, y);
		break;
	}
	case OBJECT_TYPE_TURTLE:
	{
		float type = (float)atof(tokens[3].c_str());
		float isFly = (float)atof(tokens[4].c_str());
		obj = new CTurtle(x, y, type, isFly);
		CTurtle obj2 = CTurtle(x, y, type, isFly);
		obj2.id = objId;
		reSurrectionObjects.push_back(obj2);
		break;
	}
	case OBJECT_TYPE_TELEPORT:
	{
		float type = (float)atof(tokens[3].c_str());
		float teleX = (float)atof(tokens[4].c_str());
		float teleY = (float)atof(tokens[5].c_str());
		obj = new CTeleport(x, y, type, teleX, teleY);
		break;
	}
	case OBJECT_TREE:
	{
		obj = new CTree(x, y);
		break;
	}
	case OBJECT_CAMEL:
	{
		obj = new CCamel(x, y);
		break;
	}
	case OBJECT_INTRO:
	{
		
		obj = new CIntro(x, y);
		intro = (CIntro*)obj;
		break;
	}
	
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	obj->id = objId;
	obj->SetPosition(x, y);
	objects.push_back(obj);
}

void CPlayScene::_ParseSection_MAPS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	wstring mapInformationPath = ToWSTR(tokens[0]);
	wstring MatrixPath = ToWSTR(tokens[1]);
	map = new Map();
	if (id != INTRO_SCREEN_ID)
	{
		map->LoadInformation(mapInformationPath.c_str());
		map->LoadMatrix(MatrixPath.c_str());
		map->CreateTilesFromTileSet();
	}
	if(id == WORLD_1_ID)
	{
		wstring WorldMatrixPath = ToWSTR(tokens[2]);
		map->LoadWorldMap(WorldMatrixPath.c_str());
	}
	if(id != WORLD_1_ID && id != INTRO_SCREEN_ID)
	{
		this->gameTime = atoi(tokens[2].c_str());
	}
	else
	{
		this->gameTime = 0;
	}
	DebugOut(L"\nParseSection_MAPS: Done");
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	int objId = 0;
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[MAPS]") { section = SCENE_SECTION_MAPS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_MAPS: _ParseSection_MAPS(line); break;
		case SCENE_SECTION_OBJECTS:
		{
			_ParseSection_OBJECTS(line, objId);
			objId++;
			break;
		}
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

bool CPlayScene::LinearSearch(int x)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->id == x)
			return true;
	}
	return false;
}

void CPlayScene::Update(DWORD dt)
{

	CGame* game = CGame::GetInstance();
	float cx1, cy1;
	CGame::GetInstance()->GetCamPos(cx1, cy1);
	float l = cx1;
	float t = cy1;
	float r = l + game->GetBackBufferWidth();
	float b = t + game->GetBackBufferHeight();
	
	if (id != INTRO_SCREEN_ID && id != WORLD_1_ID)
	{
		for (size_t i = 0; i < reSurrectionObjects.size(); i++)
		{
			if (!LinearSearch(reSurrectionObjects[i].id))
			{
				CGameObject* obj = new CTurtle(reSurrectionObjects[i].x, reSurrectionObjects[i].y, reSurrectionObjects[i].isRed, reSurrectionObjects[i].isFly);
				obj->id = reSurrectionObjects[i].id;
				float objL, objT, objR, objB;
				obj->GetBoundingBox(objL, objT, objR, objB);
				if (!(objL > l - (objR - objL) && objR < r + (objR - objL) && objT > t - (objB - objT) && objB < b + (objB - objT)))
				{
					AddObject(obj);
				}
			}
		}
	}

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (id != INTRO_SCREEN_ID && id != WORLD_1_ID)
		{
			if (objects[i]->y > map->maxY * 2 && !dynamic_cast<CMario*>(objects[i]))
			{
				objects[i]->Delete();
			}
		}
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		float objL, objT, objR, objB;
		objects[i]->GetBoundingBox(objL, objT, objR, objB);
		if (objects[i]->isLoaded == true || objL > l - (objR - objL) && objR < r + (objR - objL) && objT > t - (objB - objT) && objB < b + (objB - objT))
		{
			objects[i]->isLoaded = true;
			objects[i]->Update(dt, &coObjects);
		}
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	if (cy < 0) cy = - 8;
	if (cy > map->maxY || cy > map->minY) cy = map->maxY;
	if (cx < 0) cx = -8;
	if (isInExtraMap)
	{
		if (cx < map->minExtraMapX) cx = map->minExtraMapX;
		if (cx > map->maxExtraMapX) cx = map->maxExtraMapX;
	}
	else
	{
		if (cx > map->maxX) cx = map->maxX;
	}

	CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	float l = cx;
	float t = cy;
	float r = l + game->GetBackBufferWidth();
	float b = t + game->GetBackBufferHeight();
	if (id != INTRO_SCREEN_ID)
	{
		this->map->Render(l, t, r, b);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		float objL, objT, objR, objB;
		objects[i]->GetBoundingBox(objL, objT, objR, objB);
		if (objL > l - (objR - objL) && objR < r + (objR - objL) && objT > t - (objB - objT) && objB < b + (objB - objT))
		{
			objects[i]->Render();
		}
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

void CPlayScene::AddObject(CGameObject* object)
{
	objects.push_back(object);
}
