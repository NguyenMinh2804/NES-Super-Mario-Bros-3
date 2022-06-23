#include "Intro.h"
#include "Sprites.h"

void CIntro::Render()
{
	CSprites::GetInstance()->Get(screenSpiteID)->Draw(x, y);
	if (isRenderPlayer)
	{
		int playerSpiteId;
		playerSpiteId = is1Player ? ONE_PLAYER_ID : TWO_PLAYER_ID;
		CSprites::GetInstance()->Get(playerSpiteId)->Draw(PLAYER_X, PLAYER_Y);
	}
}

void CIntro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - INTRO_SCREEN_WIDTH / 2;
	t = y - INTRO_SCREEN_HEIGHT / 2;
	r = l + INTRO_SCREEN_WIDTH;
	b = t + INTRO_SCREEN_HEIGHT;
}

void CIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - start_sceen > INTRO_SCREEN_TIME * 3)
	{
		isRenderPlayer = true;
		screenSpiteID = INTRO_SCREEN_4_ID;
	}
	else if (GetTickCount64() - start_sceen > INTRO_SCREEN_TIME * 2)
	{
		screenSpiteID = INTRO_SCREEN_3_ID;
	}	
	else if (GetTickCount64() - start_sceen > INTRO_SCREEN_TIME)
	{
		screenSpiteID = INTRO_SCREEN_2_ID;
	}
}

void CIntro::ChangeNumerPlayer()
{
	is1Player = !is1Player;
}

