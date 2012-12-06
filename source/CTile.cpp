/*
 * CTile.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: Anton L.
 */

#include "CCamera.h"
#include "CCoin.h"
#include "CFPS.h"
#include "CTile.h"
#include "CSurface.h"

#define BUMP_SPEED 3.0f

CTile::CTile() :
	TileID(0),
	TypeID(TILE_TYPE_NONE),
	SwapTileID(0),
	SwapTypeID(TILE_TYPE_NONE),
	Surf_Tileset(NULL),
	X(0), Y(0),
	Bumped(false),
	Offset(0),
	Speed(0)
{

}

void CTile::OnRender(SDL_Surface *Surf_Display, int MapX, int MapY)
{
    if (Surf_Tileset == NULL || Surf_Display == NULL || TypeID == TILE_TYPE_NONE)
    	return;

    int TilesetWidth  = Surf_Tileset->w / TILE_SIZE;
	int tX = MapX + (X * TILE_SIZE);
	int tY = MapY + (Y * TILE_SIZE);

	int TilesetX = (TileID % TilesetWidth) * TILE_SIZE;
	int TilesetY = (TileID / TilesetWidth) * TILE_SIZE;

	if (tX + TILE_SIZE >= 0 && tX <= CCamera::CameraControl.GetWindowSizeX() && tY + TILE_SIZE >= 0 && tY <= CCamera::CameraControl.GetWindowSizeY())
		CSurface::OnRender(Surf_Display, Surf_Tileset, tX, tY - Offset, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
}

void CTile::OnLoop()
{
	if (Bumped)
	{
		Offset += Speed * CFPS::FPSControl.GetSpeedFactor();

		if (Offset >= TILE_SIZE / 2)
		{
			Speed = -BUMP_SPEED;
			Offset = TILE_SIZE / 2;
		}

		if (Offset < 0)
		{
			Offset = 0;
			Bumped = false;
		}
	}
}

void CTile::Bump()
{
	if ((TypeID == TILE_TYPE_BUMPABLE || TypeID == TILE_TYPE_BUMPABLECOIN) && !Bumped)
	{
		Bumped = true;
		Speed = BUMP_SPEED;

		if (TypeID == TILE_TYPE_BUMPABLECOIN)
		{
			CCoin coin;
			coin.Spawn(X * TILE_SIZE, (Y - 1) * TILE_SIZE);
			CCoin::CoinList.push_back(coin);

			if (SwapTypeID > TILE_TYPE_NONE)
			{
				TileID = SwapTileID;
				TypeID = SwapTypeID;
				SwapTileID = 0;
				SwapTypeID = TILE_TYPE_NONE;
			}
		}
	}
}

void CTile::SetTileset(SDL_Surface *Surf_Tileset)
{
	this->Surf_Tileset = Surf_Tileset;
}

void CTile::SetPos(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}
