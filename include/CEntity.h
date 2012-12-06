/*
 * CEntity.h
 *
 *  Created on: Sep 19, 2012
 *      Author: Anton L.
 */

#ifndef CENTITY_H_
#define CENTITY_H_

#include <vector>
#include "CAnimation.h"
#include "CTile.h"

enum
{
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

enum
{
    ENTITY_FLAG_NONE     = 0,
    ENTITY_FLAG_GRAVITY  = 0x00000001,
    ENTITY_FLAG_GHOST    = 0x00000002,
    ENTITY_FLAG_MAPONLY  = 0x00000004
};

enum
{
	ENTITY_DIR_LEFT = 0,
	ENTITY_DIR_RIGHT
};

class CEntity
{
public:
	static std::vector<CEntity *> EntityList;

public:
	float X, Y;
    int Width;
    int Height;
    bool MoveLeft;
    bool MoveRight;
    int Type;
    bool Dead;
    int Flags;
    float MaxSpeedX;
    float MaxSpeedY;
	bool Run;

protected:
	CAnimation Anim_Control;
	SDL_Surface *Surf_Entity;
    float SpeedX;
    float SpeedY;
    float AccelX;
    float AccelY;
	int AnimState;
	int Direction;
    int Col_X;
    int Col_Y;
    int Col_Width;
    int Col_Height;
    bool CanJump;

public:
	CEntity();
	virtual ~CEntity();

public:
	virtual bool OnLoad(const char *File, int Width, int Height, int MaxFrames);
	virtual void OnLoop();
	virtual void OnRender(SDL_Surface *Surf_Display);
	virtual void OnCleanup();
	virtual void OnAnimate();
	virtual bool OnCollision(CEntity *Entity);

public:
	void OnMove(float MoveX, float MoveY);
	void StopMove();
	bool Collides(int oX, int oY, int oW, int oH);
	bool Jump();

protected:
	virtual void OnBumpBlock(CTile *Tile);

private:
	bool PosValid(int NewX, int NewY);
	bool PosValidTile(CTile *Tile);
	bool PosValidEntity(CEntity *Entity, int NewX, int NewY);
};

class CEntityCol
{
public:
	static std::vector<CEntityCol> EntityColList;

public:
	CEntity *EntityA;
	CEntity *EntityB;

public:
	CEntityCol();
};

#endif /* CENTITY_H_ */
