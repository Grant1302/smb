/*
 * CTile.h
 *
 *  Created on: Nov 26, 2012
 *      Author: Anton L.
 */

#ifndef CTILE_H_
#define CTILE_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include "Defines.h"

class CTile
{
public:
	short TileID;
	short TypeID;
	short SwapTileID;
	short SwapTypeID;

private:
	SDL_Surface *Surf_Tileset;
	int X, Y;
	bool Bumped;
	float Offset;
	float Speed;

public:
	CTile();

public:
	void OnRender(SDL_Surface *Surf_Display, int MapX, int MapY);
	void OnLoop();
	void Bump();
	void SetTileset(SDL_Surface *Surf_Tileset);
	void SetPos(int X, int Y);
};

#endif /* CTILE_H_ */
