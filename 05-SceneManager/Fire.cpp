#include "Fire.h"
#include "Mario.h"

CFire::CFire(float x, float y, int direction) : CGameObject(x, y)
{
	this->direction = direction;
	switch (direction)
	{
	case 1:
	{
		vx = -0.055f;
		vy = 0.02f;
		break;
	}
	case 2:
	{
		vx = -0.055f;
		vy = -0.02f;
		break;
	}
	case 3:
	{
		vx = 0.055f;
		vy = 0.02f;
		break;
	}
	case 4:
	{
		vx = 0.055f;
		vy = 0.02f;
		break;
	}
	}

	SetState(0);
}

void CFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 8 / 2;
	top = y - 8 / 2;
	right = left + 8;
	bottom = top + 8;
}

void CFire::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFire::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFire::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(110)->Render(x, y);
}

void CFire::SetState(int state)
{
	CGameObject::SetState(state);
}
