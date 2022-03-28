#pragma once
#include "GameObject.h"

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