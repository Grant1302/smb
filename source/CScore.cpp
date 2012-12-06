/*
 * CScore.cpp
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include "CScore.h"
#include "CText.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CStats.h"

#define SCORE_SPEED 1.5f

std::vector<CScore> CScore::ScoreList;

CScore::CScore() :
	X(0), Y(0),
	Alive(false),
	Offset(0),
	Speed(0)
{
}

void CScore::OnRender(SDL_Surface *Surf_Display)
{
    if (Surf_Display == NULL || !Alive)
    	return;

	SDL_Color TextColor = { 255, 255, 255 };

    CText::OnRender(Surf_Display, X - CCamera::CameraControl.GetX(), Y - Offset, Text.c_str(), TextColor);
}

void CScore::OnLoop()
{
	if (Alive)
	{
		Offset += Speed * CFPS::FPSControl.GetSpeedFactor();

		if (Offset > TILE_SIZE)
			Alive = false;
	}
}

void CScore::Spawn(int X, int Y, std::string Text)
{
	if (!Alive)
	{
		this->X = X;
		this->Y = Y;
		this->Text = Text;
		Alive = true;
		Offset = 0;
		Speed = SCORE_SPEED;
		CStats::Stats.Coins++;
		CStats::Stats.Score += 200;
	}
}

bool CScore::IsAlive()
{
	return Alive;
}
