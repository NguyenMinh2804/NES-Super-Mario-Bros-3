#include "Effect.h"
#include "Sprites.h"

void CEffect::Render()
{
	if (type == EFFECT_TAIL_ACTTACK)
	{
		CSprites::GetInstance()->Get(ID_ANI_EFFECT_TAIL_ACTTACK)->Draw(x, y);
	}
	else if (type == EFFECT_BRICK_BROKEN)
	{
		CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BRICK_BROKEN)->Render(x, y);
	}
}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - EFFECT_BBOX_WIDTH / 2;
	t = y - EFFECT_BBOX_HEIGHT / 2;
	r = l + EFFECT_BBOX_WIDTH;
	b = t + EFFECT_BBOX_HEIGHT;
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == EFFECT_TAIL_ACTTACK)
	{
		if (GetTickCount64() - effect_start > EFFECT_TIME_TAIL_ACTTACK)
		{
			this->Delete();
		}
	}
	else
	{
		vy += ay * dt;
		vx += ax * dt;
		x += vx * dt;
		y += vy * dt;
		if (GetTickCount64() - effect_start > EFFECT_TIME_BRICK_BROKEN)
		{
			this->Delete();
		}
	}

}
