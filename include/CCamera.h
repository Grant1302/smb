/*
 * CCamera.h
 *
 *  Created on: Nov 26, 2012
 *      Author: Anton L.
 */

#ifndef CCAMERA_H_
#define CCAMERA_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include "CEntity.h"

enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera
{
public:
	static CCamera CameraControl;

public:
	int TargetMode;

private:
	CEntity *Target;
	int X;
	int Y;
	int WindowSizeX;
	int WindowSizeY;

public:
	CCamera();

public:
	void OnMove(int MoveX, int MoveY);
	int GetX();
	int GetY();
	void SetPos(int X, int Y);
	void SetTarget(CEntity *Target);
	void SetWindowSize(int SizeX, int SizeY);
	int GetWindowSizeX();
	int GetWindowSizeY();
};

#endif /* CCAMERA_H_ */
