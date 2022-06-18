#include "Tail.h"
#include "Sprites.h"
#include "Goomba.h"
#include "FlyGoomba.h"
#include "FLowerFire.h"
#include "Turtle.h"
#include "BrickQuestion.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Brick2.h"
void CTail::Render()
{
	//RenderBoundingBox();
}

void CTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 14 / 2;
	t = y - 4 / 2;
	r = l + 14;
	b = t + 4;
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - attack_start > 230)
	{
		this->Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (dynamic_cast<CFlyGoomba*>(e->obj))
	{
		e->obj->Delete();
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		e->obj->Delete();
	}
	else if (dynamic_cast<CFlowerFire*>(e->obj))
	{
		e->obj->Delete();
	}
	else if (dynamic_cast<CBrick2*>(e->obj))
	{
		CBrick2* brick = dynamic_cast<CBrick2*>(e->obj);
		brick->DropItem();
	}
	else if (dynamic_cast<CBrickQuestion*>(e->obj))
	{
		CBrickQuestion* brick = dynamic_cast<CBrickQuestion*>(e->obj);
		if (brick->GetState() != 0)
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion*>(e->obj);
			brickQuestion->SetState(0);
			brickQuestion->DropItem(mario->level);
		}
	}
	else if (dynamic_cast<CTurtle*>(e->obj))
	{
		CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
		turtle->SetState(TURTLE_STATE_SHELL);
	}
}
