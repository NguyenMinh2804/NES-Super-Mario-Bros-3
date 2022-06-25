#include "Turtle.h"
#include "InvisibleWall.h"
#include "Goomba.h"
#include "FlyGoomba.h"
#include "BrickQuestion.h"
#include "Brick2.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Tail.h"
#include "Coin.h"
#include "FLowerFire.h"

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
		ID_ANI_TURTLE_WALKING_LEFT = ID_ANI_TURTLE_RED_WALKING_LEFT;
		ID_ANI_TURTLE_WALKING_RIGHT = ID_ANI_TURTLE_RED_WALKING_RIGHT
		ID_ANI_TURTLE_SHELL = ID_ANI_TURTLE_RED_SHELL;
		ID_ANI_TURTLE_ATTACK = ID_ANI_TURTLE_RED_ATTACK;
	}
	else
	{
		ID_ANI_TURTLE_WALKING_LEFT = ID_ANI_TURTLE_GREEN_WALKING_LEFT;
		ID_ANI_TURTLE_WALKING_RIGHT = ID_ANI_TURTLE_GREEN_WALKING_RIGHT;
		ID_ANI_TURTLE_SHELL = ID_ANI_TURTLE_GREEN_SHELL;
		ID_ANI_TURTLE_ATTACK = ID_ANI_TURTLE_GREEN_ATTACK;
	}

}

void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TURTLE_STATE_SHELL || state == TURTLE_STATE_SHELL_ACTTACK_RIGHT || state == TURTLE_STATE_SHELL_ACTTACK_LEFT)
	{
		left = x - (TURTLE_BBOX_WIDTH - 2) / 2;
		top = y - TURTLE_BBOX_HEIGHT_SHELL / 2;
		right = left + (TURTLE_BBOX_WIDTH - 2);
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
	if (dynamic_cast<CTail*>(e->obj))
	{
		if (isFly)
		{
			isFly = false;
			return;
		}
		else
		{
			this->SetState(TURTLE_STATE_SHELL);
			return;
		}
	}
	if (state == TURTLE_STATE_WALKING)
	{
		if (!e->obj->IsBlocking() && !dynamic_cast<CInvisibleWall*>(e->obj)) return;
	}
	else if (state == TURTLE_STATE_SHELL_ACTTACK_RIGHT || state == TURTLE_STATE_SHELL_ACTTACK_LEFT)
	{
		if (dynamic_cast<CGoomba*>(e->obj) || dynamic_cast<CFlyGoomba*>(e->obj) || dynamic_cast<CTurtle*>(e->obj) || dynamic_cast<CFlowerFire*>(e->obj))
		{
			e->obj->Delete();
			return;
		}
		else if (dynamic_cast<CBrickQuestion*>(e->obj))
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion*>(e->obj);
			if (brickQuestion->GetState() != BRICK_QUESTION_STATE_BROKEN)
			{
				brickQuestion->SetState(BRICK_QUESTION_STATE_BROKEN);
				brickQuestion->DropItem(mario->level);
			}
		}
		else if (dynamic_cast<CBrick2*>(e->obj))
		{
			CBrick2* brick = dynamic_cast<CBrick2*>(e->obj);
			brick->DropItem();
		}
		if (!e->obj->IsBlocking()) return;
	}
	else if (isPickUp)
	{
		if (dynamic_cast<CGoomba*>(e->obj) || dynamic_cast<CFlyGoomba*>(e->obj) || dynamic_cast<CTurtle*>(e->obj) || dynamic_cast<CFlowerFire*>(e->obj))
		{
			e->obj->Delete();
			this->Delete();
		}
	}
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

	if (state == TURTLE_STATE_SHELL)
	{
		if (isPickUp)
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			if (mario->isPickUp == false)
			{
				if (mario->nx == 1)
				{
					SetState(TURTLE_STATE_SHELL_ACTTACK_RIGHT);
				}
				else
				{
					SetState(TURTLE_STATE_SHELL_ACTTACK_LEFT);
				}
				isPickUp = false;
			}
			else
			{
				if (mario->nx == 1)
				{
					x = mario->x + 12;
				}
				else
				{
					x = mario->x - 12;
				}
				y = mario->y;
				vy = 0;
			}
		}
		if ((GetTickCount64() - shell_start > TURTLE_SHELL_TIMEOUT))
		{
			y = y - 10;
			SetState(TURTLE_STATE_WALKING);
			isPickUp = false;
		}
	}
	if ((state == TURTLE_STATE_SHELL_ACTTACK_RIGHT || state == TURTLE_STATE_SHELL_ACTTACK_LEFT) && (GetTickCount64() - attack_start > 5000))
	{
		this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTurtle::Render()
{
	int aniId;

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
		if (vx > 0)
		{
			aniId = ID_ANI_TURTLE_FLY_RIGHT;
		}
		else
		{
			aniId = ID_ANI_TURTLE_FLY_LEFT;
		}
	}
	else
	{
		if (vx > 0)
		{
			aniId = ID_ANI_TURTLE_WALKING_RIGHT;
		}
		else
		{
			aniId = ID_ANI_TURTLE_WALKING_LEFT;
		}
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
		vx = TURTLE_ATTACK_SPEED;
		attack_start = GetTickCount64();
		break;
	case TURTLE_STATE_SHELL_ACTTACK_LEFT:
		vx = -TURTLE_ATTACK_SPEED;
		attack_start = GetTickCount64();
		break;
	case TURTLE_STATE_WALKING:
		vx = -TURTLE_WALKING_SPEED;
		ay = TURTLE_GRAVITY;
		break;
	case TURTLE_STATE_FLY:
		ay = TURTLE_FLY_GRAVITY;
		vy = -TURTLE_FLY_SPEED;
		break;
	}
}
