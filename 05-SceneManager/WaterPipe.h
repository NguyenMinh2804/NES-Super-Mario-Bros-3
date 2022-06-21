#include "GameObject.h"

#define ID_ANI_WATER_PIPE_FRIST_LEFT 91
#define ID_ANI_WATER_PIPE_FRIST_RIGHT 92
#define ID_ANI_WATER_PIPE_LAST_LEFT 93
#define ID_ANI_WATER_PIPE_LAST_RIGHT 94

#define ID_ANI_WATER_PIPE_BLACK_FRIST_LEFT 95
#define ID_ANI_WATER_PIPE_BLACK_FRIST_RIGHT 96
#define ID_ANI_WATER_PIPE_BLACK_LAST_LEFT 97
#define ID_ANI_WATER_PIPE_BLACK_LAST_RIGHT 98
#define WATER_PIPE_BBOX_WIDTH 16
#define WATER_PIPE_BBOX_HEIGHT 16
#define WATER_PIPE_TYPE_GREEN 0
#define WATER_PIPE_TYPE_BLACK 1

class CWaterPipe : public CGameObject {
	int size;
	int type;
public:
	CWaterPipe(float x, float y, int size, int type)
	{
		this->x = x;
		this->y = y;
		this->size = size;
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};