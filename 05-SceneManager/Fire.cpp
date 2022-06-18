#include "Fire.h"
#include "Mario.h"

CFire::CFire(float x, float y, int direction) : CGameObject(x, y)
{
	attack_start = GetTickCount64();
	this->direction = direction;
	switch (direction)
	{
	case FIRE_UP_LEFT:
	{
		vx = -SPEED_X;
		vy = SPEED_Y;
		break;
	}
	case FIRE_DOWN_LEFT:
	{
		vx = -SPEED_X;
		vy = -SPEED_Y;
		break;
	}
	case FIRE_UP_RIGHT:
	{
		vx = SPEED_X;
		vy = -SPEED_Y;
		break;
	}
	case FIRE_DOWN_RIGHT:
	{
		vx = SPEED_X;
		vy = SPEED_Y;
		break;
	}
	}
}

void CFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BBOX_WIDTH / 2;
	top = y - FIRE_BBOX_HEIGHT / 2;
	right = left + FIRE_BBOX_WIDTH;
	bottom = top + FIRE_BBOX_HEIGHT;
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
	if (GetTickCount64() - attack_start > FIRE_TIME)
	{
		this->Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFire::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIRE)->Render(x, y);
}

void CFire::SetState(int state)
{
	CGameObject::SetState(state);
}
