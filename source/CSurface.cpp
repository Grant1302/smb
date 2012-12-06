/*
 * CSurface.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Anton L.
 */

#include "CSurface.h"

CSurface::CSurface()
{
}

SDL_Surface *CSurface::OnLoad(const char *File)
{
	SDL_Surface *Surf_Temp = NULL;
	SDL_Surface *Surf_Return = NULL;

	if ((Surf_Temp = IMG_Load(File)) == NULL)
		return NULL;

	Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

void CSurface::OnCleanup(SDL_Surface **Surf)
{
	if (*Surf)
	{
		SDL_FreeSurface(*Surf);
		*Surf = NULL;
	}
}

bool CSurface::OnRender(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y)
{
    if (Surf_Dest == NULL || Surf_Src == NULL)
        return false;

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}

bool CSurface::OnRender(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y, int X2, int Y2, int W, int H)
{
	if (Surf_Dest == NULL || Surf_Src == NULL)
		return false;

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}

bool CSurface::FillRect(SDL_Surface *Surf_Dest, short X, short Y, unsigned short Width, unsigned short Height, SDL_Color Color)
{
	if (Surf_Dest == NULL)
		return false;

	SDL_Rect Rect = { X, Y, Width, Height };

	SDL_FillRect(Surf_Dest, &Rect, SDL_MapRGB(Surf_Dest->format, Color.r, Color.g, Color.b));

	return true;
}
