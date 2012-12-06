/*
 * CPlayer.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: Anton L.
 */

#include "CPlayer.h"

CPlayer::CPlayer()
{
}

bool CPlayer::OnLoad(const char *File, int Width, int Height, int MaxFrames)
{
    if (CEntity::OnLoad(File, Width, Height, MaxFrames) == false)
        return false;

    return true;
}

void CPlayer::OnLoop()
{
    CEntity::OnLoop();
}

void CPlayer::OnRender(SDL_Surface* Surf_Display)
{
    CEntity::OnRender(Surf_Display);
}

void CPlayer::OnCleanup()
{
    CEntity::OnCleanup();
}

void CPlayer::OnAnimate()
{
    CEntity::OnAnimate();
}

bool CPlayer::OnCollision(CEntity *Entity)
{
	Jump();

	return true;
}

void CPlayer::OnBumpBlock(CTile *Tile)
{
	Tile->Bump();
}
