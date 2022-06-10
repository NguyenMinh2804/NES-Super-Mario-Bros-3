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
	l = x - 25 / 2;
	t = y - 4 / 2;
	r = l + 25;
	b = t + 4;
}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - attack_start > 300)
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
}
