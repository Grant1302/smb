/*
 * CAppStateManager.h
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifndef CAPPSTATEMANAGER_H_
#define CAPPSTATEMANAGER_H_

#include "CAppState.h"

enum
{
    APPSTATE_NONE,
    APPSTATE_STARTSCREEN,
    APPSTATE_LEVELSCREEN,
    APPSTATE_GAME,
//    APPSTATE_PAUSE,
//    APPSTATE_GAMEOVER,
//    APPSTATE_GAMECOMPLETE,
//    APPSTATE_QUITGAME
};

class CAppStateManager
{
private:
    static CAppState *ActiveAppState;

public:
    static void OnEvent(SDL_Event *Event);
    static void OnLoop();
    static void OnRender(SDL_Surface *Surf_Display);
    static void SetActiveAppState(int AppStateID);
    static CAppState *GetActiveAppState();
};

#endif /* CAPPSTATEMANAGER_H_ */
