/*
 * CAppStateStartScreen.h
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifndef CAPPSTATESTARTSCREEN_H_
#define CAPPSTATESTARTSCREEN_H_

#include "CAppState.h"
#include "CStats.h"
#include "CMap.h"
#include "CEntity.h"

class CAppStateStartScreen: public CAppState
{
	enum
	{
		START_GAME = 0,
		EXIT_GAME
	};

private:
    static CAppStateStartScreen Instance;

private:
    SDL_Surface *Surf_Logo;
    SDL_Surface *Surf_Menu;
    int Menu;
    CEntity Mario;

public:
	CAppStateStartScreen();

public:
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface *Surf_Display);
    static CAppStateStartScreen *GetInstance();
	void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
};

#endif /* CAPPSTATESTARTSCREEN_H_ */
