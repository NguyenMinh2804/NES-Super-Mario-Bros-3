#include "Button.h"
#include "Sprites.h"
#include "PlayScene.h"
#include "Brick2.h"
#include "Coin.h"

void CButton::Render()
{
	if (isPress)
	{
		CSprites::GetInstance()->Get(ID_ANI_BUTTON_PRESS)->Draw(x, y);
	}
	else
	{
		CSprites::GetInstance()->Get(ID_ANI_BUTTON)->Draw(x, y);
	}
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isPress)
	{
		l = x - BUTTON_PRESS_BBOX_WIDTH / 2;
		t = y - BUTTON_PRESS_BBOX_HEIGHT / 2;
		r = l + BUTTON_PRESS_BBOX_WIDTH;
		b = t + BUTTON_PRESS_BBOX_HEIGHT;
	}
	else
	{
		l = x - BUTTON_BBOX_WIDTH / 2;
		t = y - BUTTON_BBOX_HEIGHT / 2;
		r = l + BUTTON_BBOX_WIDTH;
		b = t + BUTTON_BBOX_HEIGHT;
	}
}

void CButton::Trigger()
{
	if (!isPress)
	{
		y = y + (BUTTON_BBOX_HEIGHT - BUTTON_PRESS_BBOX_HEIGHT);
		isPress = true;
		CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		currentScene->objects;
		for (int i = 0; i < currentScene->objects.size(); i++)
		{
			CGameObject* obj = currentScene->objects[i];
			if (dynamic_cast<CBrick2*>(obj))
			{
				obj->Delete();
				CGameObject* coin = new CCoin(obj->x, obj->y, 0, isPress);
				currentScene->AddObject(coin);
			}
		}
	}

}

