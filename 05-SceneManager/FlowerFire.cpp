#include "FlowerFire.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"

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
		}
		else
		{
			CSprites::GetInstance()->Get(101)->Draw(x, y);
		}
	}
	else
	{
		if (cy < 320)
		{
			CSprites::GetInstance()->Get(102)->Draw(x, y);
		}
		else
		{
			CSprites::GetInstance()->Get(101)->Draw(x, y);
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
		Up();
	}
	else if (state == 1)
	{
		SetState(2);
	}
	else
	{
		Down();
	}
}
void CFlowerFire::Up()
{
	if (y > 344)
	{
		y = y - 0.3;
		return;
	}
	SetState(1);
}
void CFlowerFire::Down()
{
	if (y < 378)
	{
		y = y + 0.3;
		return;
	}
	SetState(0);
}
void CFlowerFire::SetState(int state)
{
	CGameObject::SetState(state);
}