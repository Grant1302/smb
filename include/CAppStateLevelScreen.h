/*
 * CAppStateLevelScreen.h
 *
 *  Created on: 05.10.2012
 *      Author: Anton L.
 */

#ifndef CAPPSTATELEVELSCREEN_H_
#define CAPPSTATELEVELSCREEN_H_

#include "CAppState.h"
#include "CStats.h"
#include "CSurface.h"

class CAppStateLevelScreen: public CAppState
{
private:
    static CAppStateLevelScreen Instance;

private:
    unsigned int StartTime;
    SDL_Surface *Mario;

public:
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface *Surf_Display);
    static CAppStateLevelScreen *GetInstance();

private:
	CAppStateLevelScreen();
};

#endif /* CAPPSTATELEVELSCREEN_H_ */
