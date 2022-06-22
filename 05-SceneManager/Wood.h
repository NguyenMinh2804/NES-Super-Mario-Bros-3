#pragma once
#include "GameObject.h"

#define ID_ANI_WOOD 81
#define WOOD_BBOX_WIDTH 16
#define WOOD_BBOX_HEIGHT 16
#define ID_ANI_WORLD1 82
#define ID_ANI_WORLD2 83
#define ID_ANI_WORLD3 84
#define ID_ANI_WORLD4 85
#define ID_ANI_WORLD5 86
#define ID_ANI_WORLD6 87
#define ID_ANI_WORLD_START 88
#define ID_ANI_WORLD_HEART 89
#define ID_ANI_WORLD_HELP 8011

class CWood : public CGameObject {
	int type;
public:
	CWood(float x, float y, int type)
	{
		this->type = type;
		this->x = x;
		this->y = y;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};