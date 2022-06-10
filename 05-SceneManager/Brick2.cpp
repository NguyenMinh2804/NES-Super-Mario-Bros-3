#include "Brick2.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Leaf.h"
#include "Button.h"
#include "BrickQuestion.h"

void CBrick2::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(190)->Render(x, y);
}

void CBrick2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
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
	if (type == 1)
	{
		obj = new CButton(x, y - 16);
		obj2 = new CBrickQuestion(x, y, 1);
		obj2->SetState(0);
		currentScene->AddObject(obj);
		currentScene->AddObject(obj2);
	}
	this->Delete();
}
