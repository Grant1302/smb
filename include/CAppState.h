/*
 * CAppState.h
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifndef CAPPSTATE_H_
#define CAPPSTATE_H_

#include "CEvent.h"
#include "CStats.h"

class CAppState: public CEvent
{
protected:
    static CStats Stats;

public:
	CAppState();

public:
    virtual void OnActivate() = 0;
    virtual void OnDeactivate() = 0;
    virtual void OnLoop() = 0;
    virtual void OnRender(SDL_Surface *Surf_Display) = 0;
};

#endif /* CAPPSTATE_H_ */
