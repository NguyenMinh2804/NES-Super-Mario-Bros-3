#include "GameObject.h"

#define ID_ANI_WATER_PIPE_FRIST_LEFT 91
#define ID_ANI_WATER_PIPE_FRIST_RIGHT 92
#define ID_ANI_WATER_PIPE_LAST_LEFT 93
#define ID_ANI_WATER_PIPE_LAST_RIGHT 94

#define WATER_PIPE_BBOX_WIDTH 16
#define WATER_PIPE_BBOX_HEIGHT 16

class CWaterPipe : public CGameObject {
	int size;
public:
	CWaterPipe(float x, float y, int size)
	{
		this->x = x;
		this->y = y;
		this->size = size;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};