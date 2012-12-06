/*
 * CAppStateGame.cpp
 *
 *  Created on: 19.11.2012
 *      Author: Anton L.
 */

#include "CAppStateGame.h"
#include "CAppStateManager.h"
#include "CCamera.h"
#include "CCoin.h"
#include "CFPS.h"
#include "CScore.h"
#include "CSurface.h"
#include "CText.h"
#include "Defines.h"

CAppStateGame CAppStateGame::Instance;

CAppStateGame::CAppStateGame() :
	GameState(gsPlay)
{
}

void CAppStateGame::OnActivate()
{
    if (!Mario.OnLoad(PATH_MARIO, TILE_SIZE, TILE_SIZE, 4))
		CAppStateManager::SetActiveAppState(APPSTATE_NONE);

    if (!CMap::MapControl.OnLoad(PATH_LEVEL1))
		CAppStateManager::SetActiveAppState(APPSTATE_NONE);

    CMap::MapControl.SetBackColor(35, 135, 255);

	CEntity::EntityList.clear();
    CEntity::EntityList.push_back(&Mario);
	Mario.X = CMap::MapControl.StartX;
	Mario.Y = CMap::MapControl.StartY;

    CCamera::CameraControl.SetTarget(&Mario);

    CCoin::Surf_Coin = CSurface::OnLoad(PATH_COIN);

    CStats::Stats.Save();
    CStats::Stats.SetTime(201);
}

void CAppStateGame::OnDeactivate()
{
	CSurface::OnCleanup(&CCoin::Surf_Coin);
	CMap::MapControl.OnCleanup();
	Mario.OnCleanup();
}

void CAppStateGame::OnLoop()
{
	CFPS::FPSControl.OnLoop();

	if (GameState == gsPlay)
	{
		CStats::Stats.OnLoop();
		CMap::MapControl.OnLoop();

		for (std::vector<CEntity *>::iterator i = CEntity::EntityList.begin(); i < CEntity::EntityList.end(); i++)
		{
		    if (*i)
		    	(*i)->OnLoop();
		}

		while (CCoin::CoinList.size() > 0 && !CCoin::CoinList.front().IsAlive())
			CCoin::CoinList.erase(CCoin::CoinList.begin());

		for (std::vector<CCoin>::iterator i = CCoin::CoinList.begin(); i < CCoin::CoinList.end(); i++)
			i->OnLoop();

		while (CScore::ScoreList.size() > 0 && !CScore::ScoreList.front().IsAlive())
			CScore::ScoreList.erase(CScore::ScoreList.begin());

		for (std::vector<CScore>::iterator i = CScore::ScoreList.begin(); i < CScore::ScoreList.end(); i++)
			i->OnLoop();

		for (std::vector<CEntityCol>::iterator i = CEntityCol::EntityColList.begin(); i < CEntityCol::EntityColList.end(); i++)
		{
		    CEntity *EntityA = i->EntityA;
		    CEntity *EntityB = i->EntityB;

		    if (EntityA == NULL || EntityB == NULL)
		    	continue;

		    if (EntityA->OnCollision(EntityB))
		        EntityB->OnCollision(EntityA);
		}

		CEntityCol::EntityColList.clear();
	}
}

void CAppStateGame::OnRender(SDL_Surface *Surf_Display)
{
	SDL_Color TextColor = { 255, 255, 255 };

	CMap::MapControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), 0);

	for (std::vector<CEntity *>::iterator i = CEntity::EntityList.begin(); i < CEntity::EntityList.end(); i++)
		(*i)->OnRender(Surf_Display);

	for (std::vector<CCoin>::iterator i = CCoin::CoinList.begin(); i < CCoin::CoinList.end(); i++)
		i->OnRender(Surf_Display);

	for (std::vector<CScore>::iterator i = CScore::ScoreList.begin(); i < CScore::ScoreList.end(); i++)
		i->OnRender(Surf_Display);

	CStats::Stats.OnRender(Surf_Display);

	switch (GameState)
	{
	case gsPause:
		CText::OnRender(Surf_Display, 140, 100, "Pause", TextColor);
		break;
	case gsQuitGame:
		CText::OnRender(Surf_Display, 130, 100, "Quit(Y/N)", TextColor);
		break;
	default:
		break;
	}

	char buf[32];
	sprintf(buf, "%d", CFPS::FPSControl.GetFPS());
	CText::OnRender(Surf_Display, 0, 0, buf, TextColor);
}

CAppStateGame *CAppStateGame::GetInstance()
{
    return &Instance;
}

void CAppStateGame::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	switch (Sym)
	{
	case SDLK_p:
		if (GameState == gsPause)
			GameState = gsPlay;
		else
			GameState = gsPause;
		break;

	case SDLK_q:
		GameState = gsQuitGame;
		break;

	case SDLK_y:
		if (GameState == gsQuitGame)
			CAppStateManager::SetActiveAppState(APPSTATE_NONE);
		break;

	case SDLK_n:
		if (GameState == gsQuitGame)
			GameState = gsPlay;
		break;

	case SDLK_LEFT:
		Mario.MoveLeft = true;
		break;

	case SDLK_RIGHT:
		Mario.MoveRight = true;
		break;

	case SDLK_LALT:
	case SDLK_RALT:
		Mario.Jump();
	    break;

	case SDLK_LCTRL:
	case SDLK_RCTRL:
		Mario.Run = true;
		break;

	default:
		break;
	}
}

void CAppStateGame::OnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	switch (Sym)
	{
	case SDLK_LEFT:
		Mario.MoveLeft = false;
		break;

	case SDLK_RIGHT:
		Mario.MoveRight = false;
		break;

	case SDLK_LCTRL:
	case SDLK_RCTRL:
		Mario.Run = false;
		break;

	default:
		break;
	}
}
