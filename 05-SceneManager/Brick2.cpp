#include "Brick2.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Leaf.h"
#include "Button.h"
#include "Effect.h"
#include "BrickQuestion.h"

void CBrick2::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK2)->Render(x, y);
}

void CBrick2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK2_BBOX_WIDTH / 2;
	t = y - BRICK2_BBOX_HEIGHT / 2;
	r = l + BRICK2_BBOX_WIDTH;
	b = t + BRICK2_BBOX_HEIGHT;
}

void CBrick2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CBrick2::SetState(int state)
{
	CGameObject::SetState(state);
}

void CBrick2::DropItem()
{
	CGameObject* obj;
	CGameObject* obj2;
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (type == ITEM_BUTTON)
	{
		obj = new CButton(x, y - 16);
		obj2 = new CBrickQuestion(x, y, 1);
		obj2->SetState(BRICK_QUESTION_STATE_BROKEN);
		currentScene->AddObject(obj);
		currentScene->AddObject(obj2);
	}
	else if(type == ITEM_GREEN_MUSHROOM)
	{
		obj = new CMushroom(x, y - 20, TYPE_MUSHROOM_GREEN);
		obj2 = new CBrickQuestion(x, y, 1);
		obj2->SetState(BRICK_QUESTION_STATE_BROKEN);
		currentScene->AddObject(obj);
		currentScene->AddObject(obj2);
	}
	else
	{
		CGameObject* effect1 = new CEffect(x - 8, y - 8, EFFECT_BRICK_BROKEN, EFFECT_LEFT);
		CGameObject* effect2 = new CEffect(x - 8, y + 8, EFFECT_BRICK_BROKEN, EFFECT_LEFT);
		CGameObject* effect3 = new CEffect(x + 8, y - 8, EFFECT_BRICK_BROKEN, EFFECT_RIGHT);
		CGameObject* effect4 = new CEffect(x + 8, y + 8, EFFECT_BRICK_BROKEN, EFFECT_RIGHT);
		currentScene->AddObject(effect1);
		currentScene->AddObject(effect2);
		currentScene->AddObject(effect3);
		currentScene->AddObject(effect4);
	}
	this->Delete();

}
