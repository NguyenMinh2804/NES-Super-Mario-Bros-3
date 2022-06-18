#include "BrickQuestion.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Leaf.h"

void CBrickQuestion::Render()
{
	if (state == BRICK_QUESTION_STATE_BROKEN)
	{
		CSprites::GetInstance()->Get(ID_ANI_BRICK_QUESTION_BROKEN)->Draw(x, y);
	}
	else
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BRICK_QUESTION)->Render(x, y);
	}
}

void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_QUESTION_BBOX_WIDTH / 2;
	t = y - BRICK_QUESTION_BBOX_HEIGHT / 2;
	r = l + BRICK_QUESTION_BBOX_WIDTH;
	b = t + BRICK_QUESTION_BBOX_HEIGHT;
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
	if (type == HAVE_ITEM)
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
		case MARIO_LEVEL_SMALL:
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

void CBrickQuestion::OnCollisionWith(LPCOLLISIONEVENT e)
{
}