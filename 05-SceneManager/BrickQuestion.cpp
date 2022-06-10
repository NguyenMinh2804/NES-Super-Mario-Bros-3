#include "BrickQuestion.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Leaf.h"

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
		obj = new CCoin(x, y - 16, 1);
		dynamic_cast<CCoin*>(obj)->Fly();
		currentScene->AddObject(obj);
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->coin++;
	}
	else
	{
		switch (marioLevel)
		{
		case 1:
		{
			obj = new CMushroom(x, y - 16, 0);
			currentScene->AddObject(obj);
			break;
		}
		default: 
		{
			obj = new CLeaf(x, y - 40);
			currentScene->AddObject(obj);
			break;
		}
		}
	}
}
