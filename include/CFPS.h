/*
 * CFPS.h
 *
 *  Created on: Nov 27, 2012
 *      Author: Anton L.
 */

#ifndef CFPS_H_
#define CFPS_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

class CFPS
{
public:
	static CFPS FPSControl;

private:
	unsigned int OldTime;
	unsigned int LastTime;
	float SpeedFactor;
	int NumFrames;
	int Frames;

public:
	CFPS();

public:
	void OnLoop();
	int GetFPS();
	float GetSpeedFactor();
};
#endif /* CFPS_H_ */
