/*
 * CCoin.cpp
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include "CCoin.h"
#include "CSurface.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CScore.h"

#define COIN_SPEED 3.0f

std::vector<CCoin> CCoin::CoinList;
SDL_Surface *CCoin::Surf_Coin = NULL;

CCoin::CCoin() :
	X(0), Y(0),
	Alive(false),
	Offset(0),
	Speed(0)
{
	Anim_Control.MaxFrames = Surf_Coin->w / TILE_SIZE;
}

void CCoin::OnRender(SDL_Surface *Surf_Display)
{
    if (Surf_Coin == NULL || Surf_Display == NULL || !Alive)
    	return;

	CSurface::OnRender(Surf_Display, Surf_Coin, X - CCamera::CameraControl.GetX(), Y - Offset, Anim_Control.GetCurrentFrame() * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
}

void CCoin::OnLoop()
{
	if (Alive)
	{
		Offset += Speed * CFPS::FPSControl.GetSpeedFactor();

		if (Offset >= TILE_SIZE)
		{
			Speed = -COIN_SPEED;
			Offset = TILE_SIZE;
		}

		if (Offset < 0)
		{
			Offset = 0;
			Alive = false;

			CScore score;
			score.Spawn(X, Y, "200");
			CScore::ScoreList.push_back(score);
		}
	}
	Anim_Control.OnAnimate();
}

void CCoin::Spawn(int X, int Y)
{
	if (!Alive)
	{
		this->X = X;
		this->Y = Y;
		Alive = true;
		Speed = COIN_SPEED;
	}
}

bool CCoin::IsAlive()
{
	return Alive;
}
