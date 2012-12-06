/*
 * CAppStateLevelScreen.cpp
 *
 *  Created on: 05.10.2012
 *      Author: Anton L.
 */

#include "CAppStateLevelScreen.h"
#include "CAppStateManager.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"
#include "CText.h"
#include "Defines.h"

CAppStateLevelScreen CAppStateLevelScreen::Instance;

CAppStateLevelScreen::CAppStateLevelScreen() :
	StartTime(0),
	Mario(NULL)
{
}

void CAppStateLevelScreen::OnActivate()
{
	if ((Mario = CSurface::OnLoad(PATH_MARIO)) == NULL)
		CAppStateManager::SetActiveAppState(APPSTATE_NONE);

	StartTime = SDL_GetTicks();
}

void CAppStateLevelScreen::OnDeactivate()
{
	CSurface::OnCleanup(&Mario);
}

void CAppStateLevelScreen::OnLoop()
{
	if (SDL_GetTicks() - StartTime > 3000)
		CAppStateManager::SetActiveAppState(APPSTATE_GAME);

	CFPS::FPSControl.OnLoop();
}

void CAppStateLevelScreen::OnRender(SDL_Surface *Surf_Display)
{
	char text[32];
	SDL_Color ClearColor = { 0, 0, 0 };
	SDL_Color TextColor = { 255, 255, 255 };

	CSurface::FillRect(Surf_Display, 0, 0, CCamera::CameraControl.GetWindowSizeX(), CCamera::CameraControl.GetWindowSizeY(), ClearColor);
	CStats::Stats.OnRender(Surf_Display);

	sprintf(text, "WORLD %d - %d", CStats::Stats.Level / 5 + 1, CStats::Stats.Level % 5);
	CText::OnRender(Surf_Display, 0, -8, text, TextColor, true, true);

	CSurface::OnRender(Surf_Display, Mario, CCamera::CameraControl.GetWindowSizeX() / 2 - TILE_SIZE, CCamera::CameraControl.GetWindowSizeY() / 2, 0, 0, TILE_SIZE, TILE_SIZE);
	sprintf(text, "x %d", CStats::Stats.Lives);
	CText::OnRender(Surf_Display, TILE_SIZE / 2, 8, text, TextColor, true, true);
}

CAppStateLevelScreen *CAppStateLevelScreen::GetInstance()
{
    return &Instance;
}
