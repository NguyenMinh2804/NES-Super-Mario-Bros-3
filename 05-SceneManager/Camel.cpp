#include "Camel.h"

void CCamel::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CAMEL_BBOX_WIDTH / 2;
	top = y - CAMEL_BBOX_HEIGHT / 2;
	right = left + CAMEL_BBOX_WIDTH;
	bottom = top + CAMEL_BBOX_HEIGHT;
}


void CCamel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	vx += ax * dt;
	if (abs(startX - x) > CAMEL_DISTANCE_MAX)
	{
		vx = -vx;
	}
	CGameObject::Update(dt, coObjects);
}


void CCamel::Render()
{
	if (vx > 0)
	{
		CAnimations::GetInstance()->Get(ID_ANI_CAMEL_WALKING_RIGHT)->Render(x, y);
	}
	else
	{
		CAnimations::GetInstance()->Get(ID_ANI_CAMEL_WALKING_LEFT)->Render(x, y);
	}
}

