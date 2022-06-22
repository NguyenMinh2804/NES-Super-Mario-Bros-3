#include "GameObject.h"

#define TREE_BBOX_WIDTH 16
#define TREE_BBOX_HEIGHT 16
#define ANI_TREE_ID 20

class CTree : public CGameObject {
public:
	CTree(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	virtual int IsBlocking() { return 1; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};