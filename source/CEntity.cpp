/*
 * CEntity.cpp
 *
 *  Created on: Sep 19, 2012
 *      Author: Anton L.
 */

#include "CAppStateManager.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CFPS.h"
#include "CMap.h"
#include "CStats.h"
#include "CSurface.h"
#include "Defines.h"

std::vector<CEntity *> CEntity::EntityList;
std::vector<CEntityCol> CEntityCol::EntityColList;

CEntityCol::CEntityCol() :
	EntityA(NULL),
	EntityB(NULL)
{
}

CEntity::CEntity() :
	X(0), Y(0),
	Width(0), Height(0),
	MoveLeft(false), MoveRight(false),
	Type(ENTITY_TYPE_GENERIC),
	Dead(false),
	Flags(ENTITY_FLAG_GRAVITY),
	MaxSpeedX(4), MaxSpeedY(10),
	Run(false),
	Surf_Entity(NULL),
	SpeedX(0), SpeedY(0),
	AccelX(0), AccelY(0),
	AnimState(0),
	Direction(ENTITY_DIR_RIGHT),
	Col_X(0), Col_Y(0),
	Col_Width(0), Col_Height(0),
	CanJump(false)
{
}

CEntity::~CEntity()
{
}

bool CEntity::OnLoad(const char *File, int Width, int Height, int MaxFrames)
{
    if ((Surf_Entity = CSurface::OnLoad(File)) == NULL)
        return false;

    this->Width = Width;
    this->Height = Height;

    Anim_Control.MaxFrames = MaxFrames;

    Dead = false;
    SpeedX = 0;
    SpeedY = 0;
    AccelX = 0;
    AccelY = 0;
    CanJump = true;

    return true;
}

void CEntity::OnLoop()
{
	if (!Dead)
	{
		if (Y > CCamera::CameraControl.GetWindowSizeY() - TILE_SIZE)
		{
			Dead = true;
			SpeedX = 0;
			AccelX = 0;
			SpeedY = -MaxSpeedY;
			Y = CCamera::CameraControl.GetWindowSizeY() - TILE_SIZE;
		}
	}
	else
	{
		if (Y > CCamera::CameraControl.GetWindowSizeY() - TILE_SIZE)
		{
			CStats::Stats.Lives--;

			if (CStats::Stats.Lives == 0)
				CAppStateManager::SetActiveAppState(APPSTATE_NONE);
			else
			{
				CStats::Stats.Load();
				CAppStateManager::SetActiveAppState(APPSTATE_LEVELSCREEN);
			}
		}
	}

	if (MoveLeft == false && MoveRight == false)
		StopMove();

	if (!Dead)
	{
		if (MoveLeft)
		{
			if (Run)
				AccelX = -2.0f;
			else
				AccelX = -1.0f;

			Direction = ENTITY_DIR_LEFT;
		}
		else if (MoveRight)
		{
			if (Run)
				AccelX = 2.0f;
			else
				AccelX = 1.0f;

			Direction = ENTITY_DIR_RIGHT;
		}
	}

	if (Flags & ENTITY_FLAG_GRAVITY)
		AccelY = 0.75f;

	SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	int MaxSpeedX = this->MaxSpeedX;

	if (Run)
		MaxSpeedX *= 2;

	if (SpeedX > MaxSpeedX)
		SpeedX = MaxSpeedX;
	if (SpeedX < -MaxSpeedX)
		SpeedX = -MaxSpeedX;
	if (SpeedY > MaxSpeedY)
		SpeedY = MaxSpeedY;
	if (SpeedY < -MaxSpeedY)
		SpeedY = -MaxSpeedY;

	OnMove(SpeedX, SpeedY);
	OnAnimate();
}

void CEntity::OnRender(SDL_Surface *Surf_Display)
{
    if (Surf_Entity == NULL || Surf_Display == NULL)
    	return;

    CSurface::OnRender(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height);
}

void CEntity::OnCleanup()
{
	CSurface::OnCleanup(&Surf_Entity);
}

bool CEntity::OnCollision(CEntity *Entity)
{
	return true;
}

void CEntity::OnAnimate()
{
	if (SpeedY == 0)
	{
		if (SpeedX == 0)
		{
			if (Direction == ENTITY_DIR_RIGHT)
				AnimState = 0;
			else
				AnimState = 4;
		}
		else
		{
			if (SpeedX > 0)
			{
				if (MoveRight)
					AnimState = 1;
				else
					AnimState = 2;
			}
			else
			{
				if (MoveLeft)
					AnimState = 5;
				else
					AnimState = 6;
			}
		}
	}
	else
	{
		if (Direction == ENTITY_DIR_RIGHT)
			AnimState = 3;
		else
			AnimState = 7;
	}

	if (Run)
		Anim_Control.SetFrameRate(50);
	else
		Anim_Control.SetFrameRate(100);

	Anim_Control.OnAnimate();
}

void CEntity::OnMove(float MoveX, float MoveY)
{
    if (MoveX == 0 && MoveY == 0)
    	return;

    double NewX = 0;
    double NewY = 0;

    MoveX *= CFPS::FPSControl.GetSpeedFactor();
    MoveY *= CFPS::FPSControl.GetSpeedFactor();

    if (MoveX != 0)
    {
        if (MoveX >= 0)
        	NewX = CFPS::FPSControl.GetSpeedFactor();
        else
        	NewX = -CFPS::FPSControl.GetSpeedFactor();
    }

    if (MoveY != 0)
    {
        if (MoveY >= 0)
        	NewY = CFPS::FPSControl.GetSpeedFactor();
        else
        	NewY = -CFPS::FPSControl.GetSpeedFactor();
    }

    while (true)
    {
        if (Flags & ENTITY_FLAG_GHOST)
        {
            PosValid((int)(X + NewX), (int)(Y + NewY));
            X += NewX;
            Y += NewY;
        }
        else
        {
            if (PosValid((int)(X + NewX), (int)(Y)))
                X += NewX;
            else
                SpeedX = 0;

            if (PosValid((int)(X), (int)(Y + NewY)))
            {
                Y += NewY;

                if (MoveY > 0)
                	CanJump = false;
            }
            else
            {
                if (MoveY > 0)
                    CanJump = true;

                SpeedY = 0;
            }
        }
        MoveX += -NewX;
        MoveY += -NewY;

        if ((NewX > 0 && MoveX <= 0) || (NewX < 0 && MoveX >= 0))
        	NewX = 0;

        if ((NewY > 0 && MoveY <= 0) || (NewY < 0 && MoveY >= 0))
			NewY = 0;

        if (MoveX == 0)
        	NewX = 0;
        if (MoveY == 0)
        	NewY = 0;

        if ((MoveX == 0 && MoveY == 0) || (NewX == 0 && NewY == 0))
        	break;
    }
}

void CEntity::StopMove()
{
    if (SpeedX > 0)
        AccelX = -1.0f;

    if (SpeedX < 0)
        AccelX = 1.0f;

    if (SpeedX < 1.0f && SpeedX > -1.0f)
    {
        AccelX = 0;
        SpeedX = 0;
    }
}

bool CEntity::Collides(int oX, int oY, int oW, int oH)
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    int tX = (int)X + Col_X;
    int tY = (int)Y + Col_Y;

    left1 = tX;
    left2 = oX;

    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;

    top1 = tY;
    top2 = oY;

    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;

    if (bottom1 < top2 || top1 > bottom2 || right1 < left2 || left1 > right2)
    	return false;

    return true;
}

bool CEntity::PosValid(int NewX, int NewY)
{
    bool Return = true;

    int StartX = (NewX + Col_X) / TILE_SIZE;
    int StartY = (NewY + Col_Y) / TILE_SIZE;

    int EndX = ((NewX + Col_X) + Width - Col_Width - 1) / TILE_SIZE;
    int EndY = ((NewY + Col_Y) + Height - Col_Height - 1) / TILE_SIZE;

    for (int iY = StartY; iY <= EndY; iY++)
    {
        for (int iX = StartX; iX <= EndX; iX++)
        {
            CTile *Tile = CMap::MapControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);

            if (PosValidTile(Tile) == false)
            {
                Return = false;

                if (iY < (int)Y / TILE_SIZE)
                    OnBumpBlock(Tile);
            }
        }
    }

    if (Flags & ENTITY_FLAG_MAPONLY)
    {
    }
    else
    {
        for (unsigned int i = 0; i < EntityList.size(); i++)
        {
            if (PosValidEntity(EntityList[i], NewX, NewY) == false)
                Return = false;
        }
    }

    return Return;
}

bool CEntity::PosValidTile(CTile *Tile)
{
    if (Tile == NULL)
        return true;

    if (Tile->TypeID == TILE_TYPE_BLOCK || Tile->TypeID == TILE_TYPE_BUMPABLE || Tile->TypeID == TILE_TYPE_BUMPABLECOIN)
        return false;

    return true;
}

bool CEntity::PosValidEntity(CEntity *Entity, int NewX, int NewY)
{
    if (this != Entity && Entity != NULL && !Entity->Dead && (Entity->Flags ^ ENTITY_FLAG_MAPONLY) &&
        Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1))
    {
        CEntityCol EntityCol;

        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;

        CEntityCol::EntityColList.push_back(EntityCol);

        return false;
    }

    return true;
}

bool CEntity::Jump()
{
    if (CanJump == false)
    	return false;

    SpeedY = -MaxSpeedY;
    CanJump = false;

    return true;
}

void CEntity::OnBumpBlock(CTile *Tile)
{
}
