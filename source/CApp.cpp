/*
 * CApp.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Anton L.
 */

#include <sys/stat.h>
#include "CApp.h"
#include "CAppStateManager.h"
#include "CText.h"
#include "Defines.h"

CApp::CApp() :
	Surf_Display(NULL),
	Running(true)
{
}

int CApp::OnExecute()
{
	if (OnInit() == false)
		return -1;

	SDL_Event Event;

	while (Running)
	{
		while (SDL_PollEvent(&Event))
			OnEvent(&Event);

		OnLoop();
		OnRender();
	}
	OnCleanup();

	return 0;
}

bool CApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	if ((Surf_Display = SDL_SetVideoMode(320, 240, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
		return false;

	CText::OnInit();
	CText::SetFont(PATH_FONT, 10);

	CStats::Stats.OnInit();
	CAppStateManager::SetActiveAppState(APPSTATE_STARTSCREEN);

	return true;
}

void CApp::OnEvent(SDL_Event *Event)
{
	CEvent::OnEvent(Event);
	CAppStateManager::OnEvent(Event);
}

void CApp::OnExit()
{
	Running = false;
}

void CApp::OnLoop()
{
	CAppStateManager::OnLoop();

	if (CAppStateManager::GetActiveAppState() == NULL)
		Running = false;
}

void CApp::OnRender()
{
	CAppStateManager::OnRender(Surf_Display);
	SDL_Flip(Surf_Display);
}

void CApp::OnCleanup()
{
	CAppStateManager::SetActiveAppState(APPSTATE_NONE);

	CText::OnCleanup();
	SDL_FreeSurface(Surf_Display);
	SDL_Quit();
}
