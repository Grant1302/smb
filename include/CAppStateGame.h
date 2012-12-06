/*
 * CAppStateGame.h
 *
 *  Created on: 19.11.2012
 *      Author: Anton L.
 */

#ifndef CAPPSTATEGAME_H_
#define CAPPSTATEGAME_H_

#include "CAppState.h"
#include "CStats.h"
#include "CMap.h"
#include "CPlayer.h"

class CAppStateGame: public CAppState
{
	enum EGameState
	{
		gsPlay = 0,
		gsPause,
		gsQuitGame
	};

private:
    static CAppStateGame Instance;

private:
    CPlayer Mario;
    EGameState GameState;

public:
	CAppStateGame();

public:
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface *Surf_Display);
    static CAppStateGame *GetInstance();
	void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
	void OnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
};

#endif /* CAPPSTATEGAME_H_ */
