#include "FlowerFire.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "fire.h"

void CFlowerFire::Render()
{
	float cx, cy;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->GetPosition(cx, cy);
	if (cx < x)
	{
		if (cy < 320)
		{
			CSprites::GetInstance()->Get(102)->Draw(x, y);
			direction = 2;
		}
		else
		{
			CSprites::GetInstance()->Get(101)->Draw(x, y);
			direction = 1;
		}
	}
	else
	{
		if (cy < 320)
		{
			CSprites::GetInstance()->Get(102)->Draw(x, y);
			direction = 3;
		}
		else
		{
			CSprites::GetInstance()->Get(101)->Draw(x, y);
			direction = 4;
		}
	}
}

void CFlowerFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 32 / 2;
	r = l + 16;
	b = t + 32;
}

void CFlowerFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == 0)
	{
		if (GetTickCount64() - up_start > 3000)
		{
			Up();
		}
		StartFire();
	}
	else if (state == 1)
	{
		if (GetTickCount64() - fire_start > 1000)
		{
			CGameObject* obj = new CFire(x, y - 8, direction);
			CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			currentScene->AddObject(obj);
			SetState(2);
		}
	}
	else
	{
		Down();
		StartUp();
	}
}

void CFlowerFire::Up()
{
	if (y > startY - 31)
	{
		y = y - 0.8;
		return;
	}
	SetState(1);
}

void CFlowerFire::Down()
{
	if (y < startY + 31)
	{
		y = y + 0.8;
		return;
	}
	SetState(0);
}

void CFlowerFire::SetState(int state)
{
	CGameObject::SetState(state);
}