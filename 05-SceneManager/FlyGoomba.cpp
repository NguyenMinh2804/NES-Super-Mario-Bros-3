#include "FlyGoomba.h"
#include "Goomba.h"
#include "InvisibleWall.h"
#include "Tail.h"

CFlyGoomba::CFlyGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FLYGOOMBA_GRAVITY;
	die_start = -1;
	isOnPlatform = true;
	isFly = true;
	vx = -FLYGOOMBA_WALKING_SPEED;
}

void CFlyGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLYGOOMBA_STATE_DIE)
	{
		left = x - FLYGOOMBA_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + FLYGOOMBA_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (isFly)
	{
		if (isOnPlatform)
		{
			left = x - FLYGOOMBA_BBOX_WIDTH / 2;
			top = y - FLYGOOMBA_BBOX_HEIGHT / 2;
			right = left + FLYGOOMBA_BBOX_WIDTH;
			bottom = top + FLYGOOMBA_BBOX_HEIGHT;
		}
		else
		{
			left = x - FLYGOOMBA_FLY_BBOX_WIDTH / 2;
			top = y - FLYGOOMBA_FLY_BBOX_HEIGHT / 2;
			right = left + FLYGOOMBA_FLY_BBOX_WIDTH;
			bottom = top + FLYGOOMBA_FLY_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - FLYGOOMBA_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_BBOX_HEIGHT / 2;
		right = left + FLYGOOMBA_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_BBOX_HEIGHT;
	}
}

void CFlyGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFlyGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTail*>(e->obj))
	{
		if (isFly)
		{
			isFly = false;
			return;
		}
		else
		{
			this->Delete();
			return;
		}
	}
	if (!e->obj->IsBlocking() && !dynamic_cast<CInvisibleWall*>(e->obj)) return;
	//if (dynamic_cast<CFlyGoomba*>(e->obj)) return;
	//if (dynamic_cast<CGoomba*>(e->obj)) return;
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
		if (isOnPlatform)
		{
			if (GetTickCount64() - walk_start > 800)
			{
				SetState(FLYGOOMBA_STATE_FLY);
			}
		}
		else
		{
			vy += ay * dt;
			StartWalk();
		}
	}
	else
	{
		vy += ay * dt;
	}
	//vy += ay * dt;
	vx += ax * dt;

	if ((state == FLYGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > FLYGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlyGoomba::Render()
{
	int aniId = ID_ANI_FLYGOOMBA_WALKING;
	if (isFly)
	{
		aniId = ID_ANI_FLYGOOMBA_FLY;
	}
	else if (state == FLYGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_FLYGOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CFlyGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLYGOOMBA_STATE_FLY:
		vy = -0.1f;
		isOnPlatform = false;
		break;
	case FLYGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (FLYGOOMBA_BBOX_HEIGHT - FLYGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}

