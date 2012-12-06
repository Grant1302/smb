/*
 * CAnimation.h
 *
 *  Created on: Sep 19, 2012
 *      Author: Anton L.
 */

#ifndef CANIMATION_H_
#define CANIMATION_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

class CAnimation
{
public:
	int MaxFrames;
	bool Oscillate;

private:
	int CurrentFrame;
	int FrameInc;
	unsigned int FrameRate;
	unsigned long OldTime;

public:
	CAnimation();

public:
	void OnAnimate();
	void SetFrameRate(int Rate);
	void SetCurrentFrame(int Frame);
	int GetCurrentFrame();
};

#endif /* CANIMATION_H_ */
