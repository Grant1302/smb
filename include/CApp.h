/*
 * CApp.h
 *
 *  Created on: Aug 29, 2012
 *      Author: Anton L.
 */

#ifndef CGAME_H_
#define CGAME_H_

#include "CEvent.h"

class CApp : public CEvent
{
private:
	SDL_Surface *Surf_Display;
	bool Running;

public:
	CApp();
	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event *Event);
	void OnExit();
	void OnLoop();
	void OnRender();
	void OnCleanup();
};

#endif /* CGAME_H_ */
