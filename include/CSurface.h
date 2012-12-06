/*
 * CSurface.h
 *
 *  Created on: Sep 18, 2012
 *      Author: Anton L.
 */

#ifndef CSURFACE_H_
#define CSURFACE_H_

#ifdef WIN32
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

class CSurface
{
public:
	CSurface();

public:
	static SDL_Surface *OnLoad(const char *File);
	static void OnCleanup(SDL_Surface **Surf);
	static bool OnRender(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y);
	static bool OnRender(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
	static bool FillRect(SDL_Surface *Surf_Dest, short X, short Y, unsigned short Width, unsigned short Height, SDL_Color Color);
};

#endif /* CSURFACE_H_ */
