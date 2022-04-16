#include "BrickQuestion.h"
#include "Mushroom.h"
#include "PlayScene.h"

void CBrickQuestion::Render()
{
	if (state == 0)
	{
		CSprites::GetInstance()->Get(125)->Draw(x, y);
	}
	else
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(120)->Render(x, y);
	}
}

void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CBrickQuestion::SetState(int state)
{
	CGameObject::SetState(state);
}

void CBrickQuestion::DropItem(int marioLevel)
{
	CGameObject* obj;
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (type == 1)
	{

	}
	else
	{
		switch (marioLevel)
		{
		case 1:
		{
			obj = new CMushroom(x + 16, y);
			currentScene->AddObject(obj);
		}
		case 2:
		{

		}
		case 3:
		{

		}
		}
	}
}
