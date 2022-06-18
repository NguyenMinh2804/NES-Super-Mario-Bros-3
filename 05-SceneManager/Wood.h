#pragma once
#include "GameObject.h"

#define ID_ANI_WOOD 81
#define WOOD_BBOX_WIDTH 16
#define WOOD_BBOX_HEIGHT 16
class CWood : public CGameObject {
public:
	CWood(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};