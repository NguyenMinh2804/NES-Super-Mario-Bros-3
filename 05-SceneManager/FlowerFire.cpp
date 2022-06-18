#include "FlowerFire.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "fire.h"
#include "Tail.h"

void CFlowerFire::Render()
{
	float cx, cy;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->GetPosition(cx, cy);
	int ani1, ani2, ani3, ani4;

	if (type == 3)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(107)->Render(x, y);
	}
	else
	{
		if (type == 1)
		{
			ani1 = 101;
			ani2 = 102;
			ani3 = 108;
			ani4 = 109;
		}
		else
		{
			ani1 = 103;
			ani2 = 104;
			ani3 = 1010;
			ani4 = 1011;
		}
		if (cx < x)
		{
			if (cy < 320)
			{
				CSprites::GetInstance()->Get(ani2)->Draw(x, y);
				direction = 2;
			}
			else
			{
				CSprites::GetInstance()->Get(ani1)->Draw(x, y);
				direction = 1;
			}
		}
		else
		{
			if (cy < 320)
			{
				CSprites::GetInstance()->Get(ani4)->Draw(x, y);
				direction = 3;
			}
			else
			{
				CSprites::GetInstance()->Get(ani3)->Draw(x, y);
				direction = 4;
			}
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
		if (type != 3)
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
			if (GetTickCount64() - fire_start > 500)
			{
				SetState(2);
			}
		
		}
			
	}
	else
	{
		Down();
		StartUp();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlowerFire::Up()
{
	if (y > startY - height)
	{
		y = y - 0.8;
		return;
	}
	SetState(1);
}

void CFlowerFire::Down()
{
	if (y < startY + height)
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

void CFlowerFire::OnNoCollision(DWORD dt)
{
}

void CFlowerFire::OnCollisionWith(LPCOLLISIONEVENT e)
{
}