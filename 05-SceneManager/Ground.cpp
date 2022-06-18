#include "Ground.h"
#include "Sprites.h"

void CGround::Render()
{
	if (type == TYPE_GROUND_FRIST)
	{
		CSprites::GetInstance()->Get(ID_ANI_GROUND_FRIST)->Draw(x, y);
	}else if(type == TYPE_GROUND_MID)
	{
		CSprites::GetInstance()->Get(ID_ANI_GROUND_MID)->Draw(x, y);
	}else
	{
		CSprites::GetInstance()->Get(ID_ANI_GROUND_LAST)->Draw(x, y);
	}
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GROUND_BBOX_WIDTH / 2;
	t = y - GROUND_BBOX_HEIGHT / 2;
	r = l + GROUND_BBOX_WIDTH;
	b = t + GROUND_BBOX_HEIGHT;
}