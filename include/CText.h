/*
 * CText.h
 *
 *  Created on: Sep 21, 2012
 *      Author: Anton L.
 */

#ifndef CTEXT_H_
#define CTEXT_H_

#ifdef WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#endif

class CText
{
private:
	static TTF_Font *Font;

public:
	CText();

public:
	static void OnInit();
	static void OnCleanup();
	static void SetFont(const char *File, int Size);
	static bool OnRender(SDL_Surface *Surf_Display, int X, int Y, const char *Text, SDL_Color Color);
	static bool OnRender(SDL_Surface *Surf_Display, int X, int Y, const char *Text, SDL_Color Color, bool CenterX, bool CenterY);
};

#endif /* CTEXT_H_ */
