#include "IntroKeyHandleEvent.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "Intro.h"

void CIntroKeyHandleEvent::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);	
	CIntro* intro = (CIntro*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->intro;
	switch (KeyCode)
	{
	case DIK_W:
		if (intro->is1Player)
		{
			CGame::GetInstance()->InitiateSwitchScene(WORLD_1_ID);
		}
		break;
	case DIK_Q:
		intro->ChangeNumerPlayer();
		break;
	}
}

void CIntroKeyHandleEvent::OnKeyUp(int KeyCode)
{
}

void CIntroKeyHandleEvent::KeyState(BYTE* states)
{
}