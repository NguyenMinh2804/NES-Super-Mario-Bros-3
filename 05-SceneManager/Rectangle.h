#include "GameObject.h"

class CRectangle : public CGameObject {
	int type;
public:
	CRectangle(float x, float y, int type)
	{
		this->x = x;
		this->y = y;
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};