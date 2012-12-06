/*
 * CEvent.h
 *
 *  Created on: Sep 19, 2012
 *      Author: Anton L.
 */

#ifndef CEVENT_H_
#define CEVENT_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

class CEvent
{
public:
	CEvent();
	virtual ~CEvent();

public:
	virtual void OnEvent(SDL_Event *Event);
	virtual void OnInputFocus();
	virtual void OnInputBlur();
	virtual void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
	virtual void OnKeyUp(SDLKey Sym, SDLMod Mod, Uint16 Unicode);
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();
	virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
	virtual void OnMouseWheel(bool Up, bool Down);
	virtual void OnLButtonDown(int mX, int mY);
	virtual void OnLButtonUp(int mX, int mY);
	virtual void OnRButtonDown(int mX, int mY);
	virtual void OnRButtonUp(int mX, int mY);
	virtual void OnMButtonDown(int mX, int mY);
	virtual void OnMButtonUp(int mX, int mY);
	virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
	virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
	virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
	virtual void OnMinimize();
	virtual void OnRestore();
	virtual void OnResize(int w,int h);
	virtual void OnExpose();
	virtual void OnExit();
	virtual void OnUser(Uint8 type, int code, void *data1, void *data2);
};

#endif /* CEVENT_H_ */
