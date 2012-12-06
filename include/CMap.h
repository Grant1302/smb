/*
 * CMap.h
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifndef CLEVEL_H_
#define CLEVEL_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include <vector>

#include "CSurface.h"
#include "CTile.h"

class CMap
{
public:
	static CMap MapControl;

public:
	SDL_Surface *Surf_Tileset;
	short StartX, StartY;

private:
	std::vector<CTile> TileList;
	short Width, Height;
	SDL_Color BackColor;

public:
	CMap();

public:
	bool OnLoad(const char *File);
	void OnRender(SDL_Surface *Surf_Display, int MapX, int MapY);
	void OnCleanup();
	void OnLoop();
	CTile *GetTile(int X, int Y);
	void SetBackColor(char R, char G, char B);
};

#endif /* CLEVEL_H_ */
