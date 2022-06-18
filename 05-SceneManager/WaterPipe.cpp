#include "WaterPipe.h"

void CWaterPipe::Render()
{
	CSprites::GetInstance()->Get(ID_ANI_WATER_PIPE_FRIST_LEFT)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_ANI_WATER_PIPE_FRIST_RIGHT)->Draw(x + WATER_PIPE_BBOX_WIDTH, y);
	for (int i = 1; i <= size; i++)
	{
		CSprites::GetInstance()->Get(ID_ANI_WATER_PIPE_LAST_LEFT)->Draw(x, y + WATER_PIPE_BBOX_HEIGHT *i);
		CSprites::GetInstance()->Get(ID_ANI_WATER_PIPE_LAST_RIGHT)->Draw(x + WATER_PIPE_BBOX_WIDTH, y + WATER_PIPE_BBOX_HEIGHT *i);
	}
}

void CWaterPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WATER_PIPE_BBOX_WIDTH / 2;
	t = y - WATER_PIPE_BBOX_HEIGHT / 2;
	r = l + WATER_PIPE_BBOX_WIDTH*2;
	b = t + WATER_PIPE_BBOX_HEIGHT * (size + 1);
}