#include "FlyGoomba.h"

CFlyGoomba::CFlyGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FlyGoomba_GRAVITY;
	die_start = -1;
	walk_start = -1;
	isOnPlatform = false;
}

void CFlyGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FlyGoomba_STATE_DIE)
	{
		left = x - FlyGoomba_BBOX_WIDTH / 2;
		top = y - FlyGoomba_BBOX_HEIGHT_DIE / 2;
		right = left + FlyGoomba_BBOX_WIDTH;
		bottom = top + FlyGoomba_BBOX_HEIGHT_DIE;
	}
	else if (!isOnPlatform)
	{
		left = x - FlyGoomba_FLY_BBOX_WIDTH / 2;
		top = y - FlyGoomba_FLY_BBOX_HEIGHT / 2;
		right = left + FlyGoomba_FLY_BBOX_WIDTH;
		bottom = top + FlyGoomba_FLY_BBOX_HEIGHT;
	}
	else
	{
		left = x - FlyGoomba_BBOX_WIDTH / 2;
		top = y - FlyGoomba_BBOX_HEIGHT / 2;
		right = left + FlyGoomba_BBOX_WIDTH;
		bottom = top + FlyGoomba_BBOX_HEIGHT;
	}
}

void CFlyGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFlyGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFlyGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0)
		{
			isOnPlatform = true;
			vy = 0;
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CFlyGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFly)
	{
		if (vy == 0)
		{
			if (GetTickCount64() - walk_start > 800)
			{
				SetState(FlyGoomba_STATE_FLY);
			}
		}
		else
		{
			SetState(FlyGoomba_STATE_WALKING);
			vy += ay * dt;
			StartWalk();
		}
	}
	else
	{
		vy += ay * dt;
	}
	vx += ax * dt;
	if ((state == FlyGoomba_STATE_DIE) && (GetTickCount64() - die_start > FlyGoomba_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	isOnPlatform = false;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlyGoomba::Render()
{
	int	aniId = ID_ANI_FlyGoomba_WALKING;
	if (isFly)
	{
		if (!isOnPlatform)
		{
			aniId = ID_ANI_FlyGoomba_FLY;
		}
		else
		{
			if (state == FlyGoomba_STATE_DIE)
			{
				aniId = ID_ANI_FlyGoomba_DIE;
			}
			else
			{
				aniId = ID_ANI_FlyGoomba_WALKING;
			}
		}
	}
	else
	{
		aniId = ID_ANI_FlyGoomba_WALKING_SMALL;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CFlyGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FlyGoomba_STATE_FLY:
		vy = -0.065f;
		break;
	case FlyGoomba_STATE_DIE:
		die_start = GetTickCount64();
		y += (FlyGoomba_BBOX_HEIGHT - FlyGoomba_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case FlyGoomba_STATE_WALKING:
		vx = -FlyGoomba_WALKING_SPEED;
		//ay = FlyGoomba_GRAVITY;
		break;
	}
}
