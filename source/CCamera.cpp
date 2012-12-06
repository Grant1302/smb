/*
 * CCamera.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: Anton L.
 */

#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera() :
	TargetMode(TARGET_MODE_NORMAL),
	Target(NULL),
	X(0), Y(0),
	WindowSizeX(0), WindowSizeY(0)
{
}

void CCamera::OnMove(int MoveX, int MoveY)
{
    X += MoveX;
    Y += MoveY;
}

int CCamera::GetX()
{
    if (Target != NULL)
    {
        if (TargetMode == TARGET_MODE_CENTER)
            return Target->X - (WindowSizeX / 2) + Target->Width / 2;

        return Target->X;
    }

    return X;
}

int CCamera::GetY()
{
    if (Target != NULL)
    {
        if (TargetMode == TARGET_MODE_CENTER)
            return Target->Y - (WindowSizeY / 2) + Target->Height / 2;

        return Target->Y;
    }

    return Y;
}

void CCamera::SetPos(int X, int Y)
{
    this->X = X;
    this->Y = Y;
}

void CCamera::SetTarget(CEntity *Target)
{
    this->Target = Target;
}

void CCamera::SetWindowSize(int SizeX, int SizeY)
{
	WindowSizeX = SizeX;
	WindowSizeY = SizeY;
}

int CCamera::GetWindowSizeX()
{
	return WindowSizeX;
}

int CCamera::GetWindowSizeY()
{
	return WindowSizeY;
}
