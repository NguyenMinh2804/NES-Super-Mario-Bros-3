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
#include "Effect.h"
void CTail::Render()
{
	//RenderBoundingBox();
}

void CTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAIL_BBOX_WIDTH / 2;
	t = y - TAIL_BBOX_HEIGHT / 2;
	r = l + TAIL_BBOX_WIDTH;
	b = t + TAIL_BBOX_HEIGHT;
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - attack_start > TAIL_ATTACK_TIME)
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
		Effect();
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		e->obj->Delete();
		Effect();
	}
	else if (dynamic_cast<CFlowerFire*>(e->obj))
	{
		e->obj->Delete();
		Effect();
	}
	else if (dynamic_cast<CBrick2*>(e->obj))
	{
		CBrick2* brick = dynamic_cast<CBrick2*>(e->obj);
		brick->DropItem();
		Effect();
	}
	else if (dynamic_cast<CBrickQuestion*>(e->obj))
	{
		CBrickQuestion* brick = dynamic_cast<CBrickQuestion*>(e->obj);
		if (brick->GetState() != BRICK_QUESTION_STATE_BROKEN)
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion*>(e->obj);
			brickQuestion->SetState(BRICK_QUESTION_STATE_BROKEN);
			brickQuestion->DropItem(mario->level);
			Effect();
		}

	}
	else if (dynamic_cast<CTurtle*>(e->obj))
	{
		CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
		turtle->SetState(TURTLE_STATE_SHELL);
		Effect();
	}
}

void CTail::Effect()
{
	int effectX = nx == 1 ? x + TAIL_BBOX_WIDTH / 2 : x - TAIL_BBOX_WIDTH / 2;
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CGameObject *effect = new CEffect(effectX, y);
	currentScene->AddObject(effect);
}