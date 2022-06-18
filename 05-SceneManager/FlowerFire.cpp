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
	int aniUpLeft, aniDownLeft, aniUpRight, aniDownRight;

	if (type == FLOWER_GREEN)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_FLOWER_GREEN)->Render(x, y);
	}
	else
	{
		if (type == FIRE_FLOWER_RED)
		{
			aniUpLeft = FIRE_FLOWER_RED_UP_LEFT;
			aniDownLeft = FIRE_FLOWER_RED_DOWN_LEFT;
			aniUpRight = FIRE_FLOWER_RED_UP_RIGHT;
			aniDownRight = FIRE_FLOWER_RED_DOWN_RIGHT;
		}
		else
		{
			aniUpLeft = FIRE_FLOWER_GREEN_UP_LEFT;
			aniDownLeft = FIRE_FLOWER_GREEN_DOWN_LEFT;
			aniUpRight = FIRE_FLOWER_GREEN_UP_RIGHT;
			aniDownRight = FIRE_FLOWER_GREEN_DOWN_RIGHT;
		}
		if (cx < x)
		{
			if (cy < Y_DEFINE)
			{
				CSprites::GetInstance()->Get(aniDownLeft)->Draw(x, y);
				direction = FIRE_DOWN_LEFT;
			}
			else
			{
				CSprites::GetInstance()->Get(aniUpLeft)->Draw(x, y);
				direction = FIRE_UP_LEFT;
			}
		}
		else
		{
			if (cy < Y_DEFINE)
			{
				CSprites::GetInstance()->Get(aniDownRight)->Draw(x, y);
				direction = FIRE_UP_RIGHT;
			}
			else
			{
				CSprites::GetInstance()->Get(aniUpRight)->Draw(x, y);
				direction = FIRE_DOWN_RIGHT;
			}
		}
	}

}

void CFlowerFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIRE_FLOWER_BBOX_WIDTH / 2;
	t = y - FIRE_FLOWER_BBOX_HEIGHT / 2;
	r = l + FIRE_FLOWER_BBOX_WIDTH;
	b = t + FIRE_FLOWER_BBOX_HEIGHT;
}

void CFlowerFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == STATE_UP)
	{
		if (GetTickCount64() - up_start > UP_TIME)
		{
			Up();
		}
		StartFire();
	}
	else if (state == STATE_DOWN)
	{
		if (type != 3)
		{
			if (GetTickCount64() - fire_start > FLOWER_FIRE_TIME)
			{
				CGameObject* obj = new CFire(x, y - 8, direction);
				CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
				currentScene->AddObject(obj);
				SetState(STATE_RELEASE_ACTTACK);
			}
		}
		else
		{
			if (GetTickCount64() - fire_start > CUT_TIME)
			{
				SetState(STATE_RELEASE_ACTTACK);
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
		y = y - UP_SPEED;
		return;
	}
	SetState(STATE_DOWN);
}

void CFlowerFire::Down()
{
	if (y < startY + height)
	{
		y = y + UP_SPEED;
		return;
	}
	SetState(STATE_UP);
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