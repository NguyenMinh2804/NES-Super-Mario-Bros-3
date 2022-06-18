#include "GameObject.h"

#define RECTANGLE_BBOX_WIDTH 16
#define RECTANGLE_BBOX_HEIGHT 16
#define RECTANGLE_TYPE_PINK 1
#define RECTANGLE_TYPE_BULE 2
#define RECTANGLE_TYPE_GREEN 3
#define RECTANGLE_TYPE_WHITE 4
#define RECTANGLE_TYPE_CLOUD 5

#define ID_ANI_RECTANGLE_PINK_FIRST 701
#define ID_ANI_RECTANGLE_PINK_MID 702
#define ID_ANI_RECTANGLE_PINK_LAST 703

#define ID_ANI_RECTANGLE_BLUE_FIRST 704
#define ID_ANI_RECTANGLE_BLUE_MID 705
#define ID_ANI_RECTANGLE_BLUE_LAST 706

#define ID_ANI_RECTANGLE_GREEN_FIRST 707
#define ID_ANI_RECTANGLE_GREEN_MID 708
#define ID_ANI_RECTANGLE_GREEN_LAST 709

#define ID_ANI_RECTANGLE_WHITE_FIRST 710
#define ID_ANI_RECTANGLE_WHITE_MID 711
#define ID_ANI_RECTANGLE_WHITE_LAST 712

#define ID_ANI_RECTANGLE_CLOUD 713

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