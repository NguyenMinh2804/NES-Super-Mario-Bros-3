#include "GameObject.h"

#define ID_ANI_GROUND_FRIST 61
#define ID_ANI_GROUND_MID 62
#define ID_ANI_GROUND_LAST 63
#define GROUND_BBOX_WIDTH 16
#define GROUND_BBOX_HEIGHT 16
#define TYPE_GROUND_FRIST 1
#define TYPE_GROUND_MID 2
#define TYPE_GROUND_LAST 3
class CGround : public CGameObject {
	int type;
public:
	CGround(float x, float y, int type)
	{
		this->x = x;
		this->y = y;
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};