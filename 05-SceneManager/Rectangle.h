#include "GameObject.h"

class CRectangle : public CGameObject {
	int type;
	int size;
public:
	CRectangle(float x, float y, int type, int size)
	{
		this->x = x;
		this->y = y;
		this->type = type;
		this->size = size;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
};