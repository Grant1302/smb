/*
 * CCoin.h
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifndef CCOIN_H_
#define CCOIN_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include "Defines.h"
#include "CAnimation.h"
#include <vector>

class CCoin
{
public:
	static std::vector<CCoin> CoinList;
	static SDL_Surface *Surf_Coin;

private:
	CAnimation Anim_Control;
	int X, Y;
	bool Alive;
	float Offset;
	float Speed;

public:
	CCoin();

public:
	void OnRender(SDL_Surface *Surf_Display);
	void OnLoop();
	void Spawn(int X, int Y);
	bool IsAlive();
};

#endif /* CCOIN_H_ */
