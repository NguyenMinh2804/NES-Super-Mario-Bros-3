#include <algorithm>
#include "debug.h"
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Rectangle.h"
#include "FlowerFire.h"
#include "Fire.h"
#include "Collision.h"
#include "BrickQuestion.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "FlyGoomba.h"
#include "InvisibleWall.h"
#include "Turtle.h"
#include "Tail.h"
#include "Brick2.h"
#include "PlayScene.h"
#include "Button.h"
#include "Teleport.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (GetTickCount64() - fly_time > MARIO_FLY_TIME)
	{
		isAllowFlying = false;
		fly_time = -1;
		isFlying = false;
	}

	//if (GetTickCount64() - game_start > gameTime)
	//{
	//	SetState(MARIO_STATE_DIE);
	//}
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (y > currentScene->map->maxY * 2 && currentScene->id != WORLD_1_ID)
	{
		SetState(MARIO_STATE_DIE);
	}
	if (currentScene->id == WORLD_1_ID)
	{
		SetState(MARIO_STATE_OPPOSITE);
	}
	Teleport();
	AutoWalk();
	if (isMoveX) MoveToPositionX();
	if (isMoveY) MoveToPositionY();
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::AutoWalk()
{
	if (isAutoWalk)
	{
		if (GetTickCount64() - auto_walk_start > MARIO_AUTO_WALK_TIME)
		{
			CGame::GetInstance()->InitiateSwitchScene(portalId);
			isAutoWalk = false;
			auto_walk_start - 1;
		}
		else
		{
			ax = MARIO_ACCEL_WALK_X;
			vx = MARIO_WALKING_SPEED / 2;
		}
	}
}
void CMario::Teleport()
{
	if (isTeleporting && GetTickCount64() - teleport_time < MARIO_TELEPORT_TIME)
	{
		vy = 0;
		y = isTeleDown ? y + MARIO_TELEPORT_SPEED : y - MARIO_TELEPORT_SPEED;
		vx = 0;
	}
	else if (!isTeleported && isTeleporting && GetTickCount64() - teleport_time > MARIO_TELEPORT_TIME)
	{
		SetPosition(teleX, teleY);
		vy = 0;
		CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		currentScene->isInExtraMap = isTeleDown ? true : false;
		isTeleported = true;
	}
	else if (!isTeleDown && isTeleporting && GetTickCount64() - teleport_time > MARIO_TELEPORT_TIME && GetTickCount64() - teleport_time < MARIO_TELEPORT_TIME + MARIO_TELEPORT_TIME)
	{
		vy = 0;
		y = y - MARIO_TELEPORT_SPEED;
		vx = 0;
	}
	else if (!isTeleDown && isTeleporting && GetTickCount64() - teleport_time > MARIO_TELEPORT_TIME + MARIO_TELEPORT_TIME)
	{
		isTeleporting = false;
		isTeleported = false;
		teleport_time = -1;
	}
	else if (isTeleDown && isTeleporting && GetTickCount64() - teleport_time > MARIO_TELEPORT_TIME)
	{
		isTeleporting = false;
		isTeleported = false;
		teleport_time = -1;
	}

}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0)
		{
			isOnPlatform = true;
			isAllowFlying = false;
			isFlying = false;
			vy = 0;
		}
	}
	else
	{
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CFlowerFire*>(e->obj))
		OnCollisionWithFlowerFire(e);
	else if (dynamic_cast<CBrickQuestion*>(e->obj))
		OnCollisionWithBrickQuestion(e);
	else if (dynamic_cast<CBrick2*>(e->obj))
		OnCollisionWithBrick2(e);
	else if (dynamic_cast<CFire*>(e->obj))
		OnCollisionWithFire(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CFlyGoomba*>(e->obj))
		OnCollisionWithFlyGoomba(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CTurtle*>(e->obj))
		OnCollisionWithTurtle(e);
	else if (dynamic_cast<CButton*>(e->obj))
		OnCollisionWithButton(e);
	else if (dynamic_cast<CTeleport*>(e->obj))
		OnCollisionWithTeleport(e);
}

void CMario::OnCollisionWithTeleport(LPCOLLISIONEVENT e)
{
	CTeleport* teleport = dynamic_cast<CTeleport*>(e->obj);
	if (teleport->type == TELEPORT_TYPE_DOWN && isPressDown == true && isTeleporting == false)
	{
		isTeleporting = true;
		teleport_time = GetTickCount64();
		this->teleX = teleport->teleX;
		this->teleY = teleport->teleY;
		this->isTeleDown = true;
	}
	else if (teleport->type == TELEPORT_TYPE_UP && isPressUp == true && isTeleporting == false)
	{
		isTeleporting = true;
		teleport_time = GetTickCount64();
		this->teleX = teleport->teleX;
		this->teleY = teleport->teleY;
		this->isTeleDown = false;
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SetLevel(level + 1);
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	e->obj->Delete();
	if (mushroom->type == TYPE_MUSHROOM_RED)
	{
		SetLevel(level + 1);
	}
}

void CMario::OnCollisionWithFire(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e)
{
	CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion*>(e->obj);
	if (e->ny > 0)
	{
		if (brickQuestion->GetState() != 0)
		{
			brickQuestion->SetState(BRICK_QUESTION_STATE_BROKEN);
			brickQuestion->DropItem(level);
		}
	}
}

void CMario::OnCollisionWithBrick2(LPCOLLISIONEVENT e)
{
	CBrick2* brick = dynamic_cast<CBrick2*>(e->obj);
	if (e->ny > 0)
	{
		brick->DropItem();
	}
}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		CButton* button = dynamic_cast<CButton*>(e->obj);
		button->Trigger();
	}
}

void CMario::OnCollisionWithTurtle(LPCOLLISIONEVENT e)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
	if (turtle->GetState() == TURTLE_STATE_SHELL || turtle->GetState() == TURTLE_STATE_SHELL_BY_TAIL)
	{
		if (isPickUp)
		{
			turtle->isPickUp = true;
		}
		else
		{
			if (e->nx < 0)
			{
				turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_RIGHT);
			}
			else if(e->nx > 0)
			{
				turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_LEFT);
			}
			else
			{
				if (x < turtle->x)
				{
					turtle->y = turtle->y - 1;
					turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_RIGHT);
				}
				else
				{
					turtle->y = turtle->y - 1;
					turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_LEFT);
				}
			}

		}
	}
	else
	{
		if (e->ny < 0)
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (turtle->GetIsFly())
			{
				turtle->SetIsFly(false);
			}
			else
			{
				turtle->SetState(TURTLE_STATE_SHELL);
			}
		}
		else
		{
			if (untouchable == 0)
			{
				if (turtle->GetState() != TURTLE_STATE_SHELL && turtle->GetState() != TURTLE_STATE_SHELL_BY_TAIL)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						level--;
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_TAIL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e)
{
	CFlyGoomba* flyGoomba = dynamic_cast<CFlyGoomba*>(e->obj);
	if (e->ny < 0)
	{
		if (flyGoomba->GetState() != FLYGOOMBA_STATE_DIE)
		{
			if (flyGoomba->GetIsFly())
			{
				flyGoomba->y = flyGoomba->y - 1;
				flyGoomba->SetIsFly(false);
			}
			else
			{
				flyGoomba->SetState(FLYGOOMBA_STATE_DIE);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (flyGoomba->GetState() != FLYGOOMBA_STATE_DIE && flyGoomba->GetState() != FLYGOOMBA_STATE_DIE_BY_TAIL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithFlowerFire(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	isAutoWalk = true;
	auto_walk_start = GetTickCount64();
	CPortal* portal = dynamic_cast<CPortal*>(e->obj);
	portal->Touch();
	portalId = portal->GetSceneId();
}

int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (state == MARIO_STATE_OPPOSITE)
	{
		aniId = ID_ANI_MARIO_SMALL_OPPOSITE;
		return aniId;
	}
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (state == MARIO_STATE_OPPOSITE)
	{
		aniId = ID_ANI_MARIO_BIG_OPPOSITE;
		return aniId;
	}
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}
	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdFly()
{
	int aniId = -1;
	if (GetTickCount64() - tail_attack < TAIL_ATTACK_TIME)
	{
		if (nx == 1)
		{
			aniId = ID_ANI_MARIO_ATTACK_RIGHT;
		}
		else
		{
			aniId = ID_ANI_MARIO_ATTACK_LEFT;
		}
		return aniId;
	}
	if (isTeleporting)
	{
		aniId = ID_ANI_MARIO_FLY_TELEPORT;
		return aniId;
	}
	if (state == MARIO_STATE_OPPOSITE)
	{
		aniId = ID_ANI_MARIO_FLY_OPPOSITE;
		return aniId;
	}
	if (!isOnPlatform)
	{
		if (ay == MARIO_SLOW_GRAVITY)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SLOW_FALL_RIGHT;
			else
				aniId = ID_ANI_MARIO_SLOW_FALL_LEFT;
		}
		else
		{
			if (isFlying)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_FLY_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_FLY_RUN_LEFT;
			}
			else if (abs(ax) == MARIO_ACCEL_RUN_X)
			{

				if (nx >= 0)
					aniId = ID_ANI_MARIO_FLY_RUN_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_FLY_RUN_JUMP_LEFT;
			}
			else
			{
				if (vy >= 0)
				{
					if (nx >= 0)
					{
						aniId = ID_ANI_MARIO_FLY_FALL_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_FLY_FALL_LEFT;
					}
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_FLY_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_FLY_WALK_LEFT;
				}

			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_FLY_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_FLY_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_FLY_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_FLY_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_FLY_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_FLY_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_FLY_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_FLY_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_FLY_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_FLY_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_FLY)
		aniId = GetAniIdFly();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d    -    Game Time: %d", coin, (gameTime - (GetTickCount64() - game_start)) / 1000);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE)
	{
		if (GetTickCount64() - start_die > MARIO_DIE_TIME)
		{
			CGame::GetInstance()->InitiateSwitchScene(WORLD_1_ID);
		}
		return;
	};

	if (isAutoWalk)
	{
		return;
	}

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		if (isFlying)
		{
			ax = MARIO_ACCEL_RUN_X;
		}
		else
		{
			if (ax < MARIO_ACCEL_RUN_X)
			{
				if (isOnPlatform)
				{
					ax += MARIO_RUN;
				}
			}
			else
			{
				ax = MARIO_ACCEL_RUN_X;
			}
		}
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		if (isFlying)
		{
			ax = -MARIO_ACCEL_RUN_X;
		}
		else
		{
			if (ax > -MARIO_ACCEL_RUN_X)
			{
				if (isOnPlatform)
				{
					ax -= MARIO_RUN;
				}
			}
			else
			{
				ax = -MARIO_ACCEL_RUN_X;
			}
		}
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			isOnPlatform = false;
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				vy = -MARIO_JUMP_RUN_SPEED_Y;
				isAllowFlying = true;
				fly_time = GetTickCount64();
			}
			else
			{
				vy = -MARIO_JUMP_SPEED_Y;
			}
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		ay = MARIO_GRAVITY;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		isAllowFlying = false;
		isFlying = false;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && !isTeleporting)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		isAllowFlying = false;
		isFlying = false;
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		isAllowFlying = false;
		isFlying = false;
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		isAllowFlying = false;
		isFlying = false;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		isAllowFlying = false;
		isFlying = false;
		start_die = GetTickCount64();
		SetLevel(MARIO_LEVEL_SMALL);
		break;
	case MARIO_STATE_SLOW_FALL:
		vy = 0;
		ay = MARIO_SLOW_GRAVITY;
		if (nx == 1)
		{
			maxVx = MARIO_WALKING_SPEED;
			ax = MARIO_ACCEL_WALK_X;
		}
		else if (nx == -1)
		{
			maxVx = -MARIO_WALKING_SPEED;
			ax = -MARIO_ACCEL_WALK_X;
		}
		isAllowFlying = false;
		isFlying = false;
		break;
	case MARIO_STATE_FLY:
		vy = -MARIO_FLY_SPEED_Y;
		isFlying = true;
		break;
	case MARIO_STATE_TAIL_ATTACK:
		isAllowFlying = false;
		isFlying = false;
		TailAttack();
		break;
	case MARIO_STATE_OPPOSITE:
		vy = 0;
		ay = 0;
		vx = 0;
		ax = 0;
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL) {
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
	else {
		if (isSitting)
		{
			left = x - MARIO_FLY_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_FLY_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_FLY_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_FLY_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_FLY_BBOX_WIDTH / 2;
			top = y - MARIO_FLY_BBOX_HEIGHT / 2;
			right = left + MARIO_FLY_BBOX_WIDTH;
			bottom = top + MARIO_FLY_BBOX_HEIGHT;
		}
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}if (l <= 3)
	{
		level = l;
		CGame* game = CGame::GetInstance();
		game->SetMarioLevel(l);
	}

}

void CMario::TailAttack()
{
	tail_attack = GetTickCount64();
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CGameObject* obj;
	obj = new CTail(x, y, nx);
	currentScene->AddObject(obj);
}

void CMario::GoRight()
{
	if (!isMoveX && !isMoveY && AllowMoveInWorldMap((x + WOLRD_MAP_TILE) / WOLRD_MAP_TILE, (y + WOLRD_MAP_TILE / 2) / WOLRD_MAP_TILE, false, true, false, false))
	{
		isMoveX = true;
		moveX = x + WOLRD_MAP_TILE;
	}
}
void CMario::GoLeft()
{
	if (!isMoveX && !isMoveY && AllowMoveInWorldMap((x - WOLRD_MAP_TILE) / WOLRD_MAP_TILE, (y + WOLRD_MAP_TILE / 2) / WOLRD_MAP_TILE, true, false, false, false))
	{
		isMoveX = true;
		moveX = x - WOLRD_MAP_TILE;
	}
}

void CMario::GoDown()
{
	if (!isMoveX && !isMoveY && AllowMoveInWorldMap(x / WOLRD_MAP_TILE, (y + WOLRD_MAP_TILE + WOLRD_MAP_TILE / 2) / WOLRD_MAP_TILE, false, false, false, true))
	{
		isMoveY = true;
		moveY = y + WOLRD_MAP_TILE;
	}
}

void CMario::GoUp()
{
	if (!isMoveX && !isMoveY && AllowMoveInWorldMap(x / WOLRD_MAP_TILE, (y - WOLRD_MAP_TILE + WOLRD_MAP_TILE / 2) / WOLRD_MAP_TILE, false, false, true, false))
	{
		isMoveY = true;
		moveY = y - WOLRD_MAP_TILE;
	}
}

void CMario::GoPlayScreen()
{
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	int screenID = currentScene->map->worldMapMatrix[int((y + WOLRD_MAP_TILE / 2) / WOLRD_MAP_TILE)][int(x / WOLRD_MAP_TILE)];
	if (screenID == WORLD_1_1_ID)
	{
		CGame::GetInstance()->InitiateSwitchScene(screenID);
	}
}

bool CMario::AllowMoveInWorldMap(int x, int y, bool isLeft, bool isRight, bool isUp, bool isDown)
{
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	int index = currentScene->map->worldMapMatrix[y][x];
	if (isDown && (index == WOLRD_BLOCK_DOWN || index == WOLRD_BLOCK_RIGHT))
	{
		return false;
	}
	else if (isUp && (index == WOLRD_BLOCK_UP || index == WOLRD_BLOCK_RIGHT))
	{
		return false;
	}
	else if (isRight && index == WOLRD_BLOCK_RIGHT)
	{
		return false;
	}
	else if (isLeft && index == WOLRD_BLOCK_LEFT)
	{
		return false;
	}
	return index;
}

void CMario::MoveToPositionX() {
	if (this->x < moveX)
	{
		x = x + MARIO_MOVE_SEED;
		isMoveX = true;
	}
	else if (this->x > moveX)
	{
		x = x - MARIO_MOVE_SEED;
		isMoveX = true;
	}
	else if (x = moveX)
	{
		isMoveX = false;
	}
}

void CMario::MoveToPositionY() {
	if (this->y < moveY)
	{
		y = y + MARIO_MOVE_SEED;
		isMoveY = true;
	}
	else if (this->y > moveY)
	{
		y = y - MARIO_MOVE_SEED;
		isMoveY = true;
	}
	else if (y = moveY)
	{
		isMoveY = false;
	}
}