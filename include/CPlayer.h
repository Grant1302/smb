/*
 * CPlayer.h
 *
 *  Created on: Nov 27, 2012
 *      Author: Anton L.
 */

#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "CEntity.h"

class CPlayer: public CEntity
{
public:
	CPlayer();
    bool OnLoad(const char *File, int Width, int Height, int MaxFrames);
    void OnLoop();
    void OnRender(SDL_Surface *Surf_Display);
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(CEntity *Entity);

private:
    void OnBumpBlock(CTile *Tile);
};

#endif /* CPLAYER_H_ */
