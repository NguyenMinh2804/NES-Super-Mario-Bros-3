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
	if (GetTickCount64() - game_start > gameTime)
	{
		SetState(MARIO_STATE_DIE);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
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
			vy = 0;
			isFlying = false;
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
	else if (dynamic_cast<CRectangle*>(e->obj))
		OnCollisionWithRectangle(e);
	else if (dynamic_cast<CTurtle*>(e->obj))
		OnCollisionWithTurtle(e);
	else if (dynamic_cast<CButton*>(e->obj))
		OnCollisionWithButton(e);
}


void CMario::OnCollisionWithRectangle(LPCOLLISIONEVENT e)
{
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SetLevel(3);
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SetLevel(2);
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
			brickQuestion->SetState(0);
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
	CButton* button = dynamic_cast<CButton*>(e->obj);
	button->Trigger();
}

void CMario::OnCollisionWithTurtle(LPCOLLISIONEVENT e)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
	if (turtle->GetState() == TURTLE_STATE_SHELL)
	{
		if (isPickUp)
		{
			turtle->isPickUp = true;
		}
		else
		{
			if (e->nx > 0)
			{
				turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_RIGHT);
			}
			else
			{
				turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_LEFT);
			}
			if (e->ny < 0)
			{
				if (x + 4 > turtle->x + 8)
				{
					turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_LEFT);
				}
				else
				{
					turtle->SetState(TURTLE_STATE_SHELL_ACTTACK_RIGHT);
				}
			}
		}
	}
	else
	{
		if (e->ny < 0)
		{
			if (turtle->GetIsFly())
			{
				turtle->SetIsFly(false);
			}
			else
			{
				turtle->SetState(TURTLE_STATE_SHELL);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			if (untouchable == 0)
			{
				if (turtle->GetState() != TURTLE_STATE_SHELL)
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
			if (goomba->GetState() != GOOMBA_STATE_DIE)
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
			if (flyGoomba->GetState() != FLYGOOMBA_STATE_DIE)
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
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
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
			if (isAllowFlying)
			{

				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_FLY_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_FLY_RUN_LEFT;
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

	DebugOutTitle(L"Coins: %d    -    Game Time: %d", isAllowFlying, (gameTime - (GetTickCount64() - game_start)) / 1000);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		if (ax < MARIO_ACCEL_RUN_X)
		{
			ax += MARIO_RUN;
			isAllowFlying = false;
		}
		else
		{
			ax = MARIO_ACCEL_RUN_X;
			isAllowFlying = true;
		}
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		if (ax > -MARIO_ACCEL_RUN_X)
		{
			ax -= MARIO_RUN;
			isAllowFlying = false;
		}
		else
		{
			ax = -MARIO_ACCEL_RUN_X;
			isAllowFlying = true;
		}
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		if(!isFlying)	isAllowFlying = false;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		if(!isFlying)	isAllowFlying = false;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			isOnPlatform = false;
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		ay = MARIO_GRAVITY;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		isAllowFlying = false;
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		isAllowFlying = false;
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		isAllowFlying = false;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		isAllowFlying = false;
		break;
	case MARIO_STATE_SLOW_FALL:
		vy = 0;
		ay = MARIO_SLOW_GRAVITY;
		isAllowFlying = false;
		break;
	case MARIO_STATE_FLY:
		isFlying = true;
		vy = -MARIO_FLY_SPEED_Y;
		break;
	case MARIO_STATE_TAIL_ATTACK:
		TailAttack();
		isAllowFlying = false;
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
	}
	level = l;
}

void CMario::TailAttack()
{
	tail_attack = GetTickCount64();
	CPlayScene* currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CGameObject* obj;
	obj = new CTail(x, y, nx);
	currentScene->AddObject(obj);
}

