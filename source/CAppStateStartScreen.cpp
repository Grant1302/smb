/*
 * CAppStateStartScreen.cpp
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#include "CAppStateStartScreen.h"
#include "CAppStateManager.h"
#include "CSurface.h"
#include "CText.h"
#include "CFPS.h"
#include "CCamera.h"
#include "Defines.h"

CAppStateStartScreen CAppStateStartScreen::Instance;

CAppStateStartScreen::CAppStateStartScreen() :
	Surf_Logo(NULL),
	Surf_Menu(NULL),
	Menu(0)
{
}

void CAppStateStartScreen::OnActivate()
{
    if ((Surf_Logo = CSurface::OnLoad(PATH_LOGO)) == NULL)
		CAppStateManager::SetActiveAppState(APPSTATE_NONE);

    if ((Surf_Menu = CSurface::OnLoad(PATH_SELECT)) == NULL)
		CAppStateManager::SetActiveAppState(APPSTATE_NONE);

    if (!Mario.OnLoad(PATH_MARIO, TILE_SIZE, TILE_SIZE, 4))
		CAppStateManager::SetActiveAppState(APPSTATE_NONE);

	if (!CMap::MapControl.OnLoad(PATH_LEVEL1))
		CAppStateManager::SetActiveAppState(APPSTATE_NONE);

    CMap::MapControl.SetBackColor(35, 135, 255);

	CEntity::EntityList.clear();
    CEntity::EntityList.push_back(&Mario);
	Mario.X = CMap::MapControl.StartX;
	Mario.Y = CMap::MapControl.StartY;

    CCamera::CameraControl.SetWindowSize(320, 240);
    CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(&Mario);

    CStats::Stats.Level = 1;
    CStats::Stats.Lives = 3;
}

void CAppStateStartScreen::OnDeactivate()
{
	CMap::MapControl.OnCleanup();
	Mario.OnCleanup();
	CSurface::OnCleanup(&Surf_Menu);
	CSurface::OnCleanup(&Surf_Logo);
}

void CAppStateStartScreen::OnLoop()
{
	CFPS::FPSControl.OnLoop();
	Mario.OnLoop();
}

void CAppStateStartScreen::OnRender(SDL_Surface *Surf_Display)
{
	SDL_Color TextColor = { 255, 255, 255 };
	int MenuOffset[2] = { 131, 147 };

	CMap::MapControl.OnRender(Surf_Display, 0, 0);
	CStats::Stats.OnRender(Surf_Display);
	Mario.OnRender(Surf_Display);

	CSurface::OnRender(Surf_Display, Surf_Logo, 55, 20);
	CSurface::OnRender(Surf_Display, Surf_Menu, 108, MenuOffset[Menu]);

	CText::OnRender(Surf_Display, 120, 130, "START GAME", TextColor);
	CText::OnRender(Surf_Display, 120, 146, "EXIT GAME", TextColor);
	CText::OnRender(Surf_Display, 120, 162, "TOP - 000000", TextColor);
}

CAppStateStartScreen *CAppStateStartScreen::GetInstance()
{
    return &Instance;
}

void CAppStateStartScreen::OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode)
{
	switch (Sym)
	{
	case SDLK_RETURN:
		switch (Menu)
		{
		case START_GAME:
			CAppStateManager::SetActiveAppState(APPSTATE_LEVELSCREEN);
			break;

		case EXIT_GAME:
			CAppStateManager::SetActiveAppState(APPSTATE_NONE);
			break;
		}
		break;

	case SDLK_UP:
		Menu = START_GAME;
		break;

	case SDLK_DOWN:
		Menu = EXIT_GAME;
		break;

	default:
		break;
	}
}
