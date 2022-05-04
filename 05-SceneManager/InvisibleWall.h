#pragma once
#include "GameObject.h"

class CInvisibleWall : public CGameObject {
public:
	CInvisibleWall(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	virtual int IsBlocking() { return 0; }

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};