#include "Turtle.h"
#include "InvisibleWall.h"
#include "Goomba.h"
#include "FlyGoomba.h"
#include "BrickQuestion.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"

CTurtle::CTurtle(float x, float y, bool isRed, bool isFly) :CGameObject(x, y)
{
	this->isFly = isFly;
	this->ax = 0;
	this->ay = TURTLE_GRAVITY;
	shell_start = -1;
	attack_start = -1;
	SetState(TURTLE_STATE_WALKING);
	this->isRed = isRed;
	if (isRed)
	{
		ID_ANI_TURTLE_WALKING = 1801;
		ID_ANI_TURTLE_SHELL = 1802;
		ID_ANI_TURTLE_ATTACK = 1803;
	}
	else
	{
		ID_ANI_TURTLE_WALKING = 1804;
		ID_ANI_TURTLE_SHELL = 1805;
		ID_ANI_TURTLE_ATTACK = 1806;
	}

}

void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TURTLE_STATE_SHELL || state == TURTLE_STATE_SHELL_ACTTACK_RIGHT || state == TURTLE_STATE_SHELL_ACTTACK_LEFT)
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT_SHELL / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT;
	}
}

void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == TURTLE_STATE_WALKING || isFly)
	{
		if (!e->obj->IsBlocking() && !dynamic_cast<CInvisibleWall*>(e->obj)) return;
	}
	else if(state == TURTLE_STATE_SHELL_ACTTACK_RIGHT || state == TURTLE_STATE_SHELL_ACTTACK_LEFT)
	{
		if (dynamic_cast<CInvisibleWall*>(e->obj))
		{
			return;
		}
		else if (dynamic_cast<CGoomba*>(e->obj) || dynamic_cast<CFlyGoomba*>(e->obj) || dynamic_cast<CTurtle*>(e->obj))
		{
			e->obj->Delete();
		}
		else if (dynamic_cast<CBrickQuestion*>(e->obj))
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			CBrickQuestion *brickQuestion = dynamic_cast<CBrickQuestion*>(e->obj);
			brickQuestion->SetState(0);
			brickQuestion->DropItem(mario->level);
		}
	}
	//if (dynamic_cast<CTurtle*>(e->obj)) return;
	//if (dynamic_cast<CFlyTurtle*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFly)
	{
		if (vy == 0)
		{
			SetState(TURTLE_STATE_FLY);
		}
		else
		{
			vy += ay * dt;
			SetState(TURTLE_STATE_WALKING);
		}
	}
	else
	{
		vy += ay * dt;
	}
	vx += ax * dt;

	if ((state == TURTLE_STATE_SHELL) && (GetTickCount64() - shell_start > TURTLE_SHELL_TIMEOUT))
	{
		y = y - 10;
		SetState(TURTLE_STATE_WALKING);
	}
	if ((state == TURTLE_STATE_SHELL_ACTTACK_RIGHT || state == TURTLE_STATE_SHELL_ACTTACK_LEFT) && (GetTickCount64() - attack_start > 10000))
	{
		this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTurtle::Render()
{
	int aniId = ID_ANI_TURTLE_WALKING;
	if (state == TURTLE_STATE_SHELL)
	{
		aniId = ID_ANI_TURTLE_SHELL;
	}
	else if (state == TURTLE_STATE_SHELL_ACTTACK_RIGHT || state == TURTLE_STATE_SHELL_ACTTACK_LEFT)
	{
		aniId = ID_ANI_TURTLE_ATTACK;
	}
	else if (isFly)
	{
		aniId = ID_ANI_TURTLE_FLY;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CTurtle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TURTLE_STATE_SHELL:
		shell_start = GetTickCount64();
		vx = 0;
		break;
	case TURTLE_STATE_SHELL_ACTTACK_RIGHT:
		vx = 0.28f;
		attack_start = GetTickCount64();
		break;
	case TURTLE_STATE_SHELL_ACTTACK_LEFT:
		vx = -0.28f;
		attack_start = GetTickCount64();
		break;
	case TURTLE_STATE_WALKING:
		ay = TURTLE_GRAVITY;
		vx = -TURTLE_WALKING_SPEED;
		break;
	case TURTLE_STATE_FLY:
		ay = 0.0002;
		vy = -0.27f;
		break;
	}
}