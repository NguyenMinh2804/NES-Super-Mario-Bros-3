#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->isPressDown = true;
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_UP:
		mario->isPressUp = true;
		break;
	case DIK_S:
		if (mario->level == 3)
		{
			if (!mario->isOnPlatform)
			{
				if (mario->isAllowFlying)
				{
					mario->SetState(MARIO_STATE_FLY);
				}
				else
				{
					mario->SetState(MARIO_STATE_SLOW_FALL);
				}
			}
			else {
				mario->SetState(MARIO_STATE_JUMP);
			}
		}
		else
		{
			mario->SetState(MARIO_STATE_JUMP);
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_FLY);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_A:
		if (mario->level == 3)
		{
			mario->SetState(MARIO_STATE_TAIL_ATTACK);
		}		
		break;
	case DIK_R:
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if(!mario->isAllowFlying)	mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_A:
		mario->isPickUp = false;
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		mario->isPressDown = false;
		break;
	case DIK_UP:
		mario->isPressUp = false;
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			mario->isPickUp = true;
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
			mario->isPickUp = true;
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else
		if (!mario->isAllowFlying) mario->SetState(MARIO_STATE_IDLE);
}