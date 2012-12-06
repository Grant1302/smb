/*
 * CAppStateManager.cpp
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#include "CAppStateManager.h"
#include "CAppStateStartScreen.h"
#include "CAppStateLevelScreen.h"
#include "CAppStateGame.h"

CAppState* CAppStateManager::ActiveAppState = NULL;

void CAppStateManager::OnEvent(SDL_Event *EventHolder)
{
    if(ActiveAppState)
    	ActiveAppState->OnEvent(EventHolder);
}

void CAppStateManager::OnLoop()
{
    if(ActiveAppState)
    	ActiveAppState->OnLoop();
}

void CAppStateManager::OnRender(SDL_Surface *Surf_Display)
{
    if (ActiveAppState)
    	ActiveAppState->OnRender(Surf_Display);
}

void CAppStateManager::SetActiveAppState(int AppStateID)
{
    if (ActiveAppState)
    	ActiveAppState->OnDeactivate();

    if (AppStateID == APPSTATE_NONE)
    	ActiveAppState = NULL;
    if (AppStateID == APPSTATE_STARTSCREEN)
    	ActiveAppState = CAppStateStartScreen::GetInstance();
    if (AppStateID == APPSTATE_LEVELSCREEN)
    	ActiveAppState = CAppStateLevelScreen::GetInstance();
    if (AppStateID == APPSTATE_GAME)
    	ActiveAppState = CAppStateGame::GetInstance();

    if (ActiveAppState)
    	ActiveAppState->OnActivate();
}

CAppState* CAppStateManager::GetActiveAppState()
{
    return ActiveAppState;
}
