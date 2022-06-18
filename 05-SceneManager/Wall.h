#include "GameObject.h"

#define WALL_BBOX_WIDTH 16
#define WALL_BBOX_HEIGHT 16
class CWall : public CGameObject {
public:
	CWall(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	virtual int IsBlocking() { return 1;}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};