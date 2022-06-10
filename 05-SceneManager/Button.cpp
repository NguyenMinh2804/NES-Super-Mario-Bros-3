#include "Button.h"
#include "Sprites.h"
#include "PlayScene.h"
#include "Brick2.h"
#include "Coin.h"

void CButton::Render()
{

	CSprites::GetInstance()->Get(201)->Draw(x, y);
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}

void CButton::Trigger()
{
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	currentScene->objects;
	for (int i = 0; i < currentScene->objects.size(); i++)
	{
		CGameObject* obj = currentScene->objects[i];
		if (dynamic_cast<CBrick2*>(obj))
		{
			obj->Delete();
			CGameObject* obj2 = new CCoin(obj->x, obj->y, 0);
			currentScene->AddObject(obj2);
		}
	}
	this->Delete();
}

