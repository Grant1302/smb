/*
 * CText.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: Anton L.
 */

#include "CCamera.h"
#include "CText.h"

TTF_Font *CText::Font = NULL;

CText::CText()
{
}

void CText::OnInit()
{
	TTF_Init();
}

void CText::OnCleanup()
{
	if (Font)
		TTF_CloseFont(Font);

	TTF_Quit();
}

void CText::SetFont(const char *File, int Size)
{
	if (Font)
		TTF_CloseFont(Font);

	Font = TTF_OpenFont(File, Size);
}

bool CText::OnRender(SDL_Surface *Surf_Display, int X, int Y, const char *Text, SDL_Color Color)
{
    if (Surf_Display == NULL || Text == NULL)
        return false;

    SDL_Rect DestR;
    SDL_Surface *Surf_Text = TTF_RenderText_Blended(Font, Text, Color);

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(Surf_Text, NULL, Surf_Display, &DestR);
    SDL_FreeSurface(Surf_Text);

    return true;
}

bool CText::OnRender(SDL_Surface *Surf_Display, int X, int Y, const char *Text, SDL_Color Color, bool CenterX, bool CenterY)
{
    if (Surf_Display == NULL || Text == NULL)
        return false;

    SDL_Rect DestR;
    SDL_Surface *Surf_Text = TTF_RenderText_Blended(Font, Text, Color);

    DestR.x = X;
    DestR.y = Y;

    if (CenterX)
    	DestR.x += (CCamera::CameraControl.GetWindowSizeX() - Surf_Text->w) / 2;
    if (CenterY)
    	DestR.y += (CCamera::CameraControl.GetWindowSizeY() - Surf_Text->h) / 2;

    SDL_BlitSurface(Surf_Text, NULL, Surf_Display, &DestR);
    SDL_FreeSurface(Surf_Text);

    return true;
}
