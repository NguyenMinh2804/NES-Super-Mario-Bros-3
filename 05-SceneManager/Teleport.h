#include "GameObject.h"

#define TELEPORT_BBOX_WIDTH 32
#define TELEPORT_BBOX_HEIGHT 16
#define TELEPORT_TYPE_DOWN 0
#define TELEPORT_TYPE_UP 1

class CTeleport : public CGameObject {
public:
	int type;
	int teleX;
	int teleY;
	CTeleport(float x, float y, int type, int teleX, int teleY)
	{
		this->x = x;
		this->y = y;
		this->type = type;
		this->teleX = teleX;
		this->teleY = teleY;
	}
	virtual int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};