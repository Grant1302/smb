/*
 * CMap.cpp
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#include "CMap.h"
#include "CCamera.h"

CMap CMap::MapControl;

CMap::CMap() :
	Surf_Tileset(NULL),
	StartX(0), StartY(0),
	Width(0), Height(0)
{
}

bool CMap::OnLoad(const char *File)
{
	OnCleanup();

	FILE *FileHandle = fopen(File, "rb");

	if (FileHandle == NULL)
		return false;

	char TilesetFile[1024] = PATH_TILESETS;
	char buf[255];
	unsigned short len;

	if (fread(&len, sizeof(len), 1, FileHandle) == 0)
		return false;
	if (fread(buf, len, 1, FileHandle) == 0)
		return false;

	strcat(TilesetFile, buf);

	if ((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false)
	{
		fclose(FileHandle);
		return false;
	}

	if (fread(&Width, sizeof(Width), 1, FileHandle) == 0)
		return false;
	if (fread(&Height, sizeof(Height), 1, FileHandle) == 0)
		return false;

	for (int Y = 0; Y < Height; Y++)
	{
		for (int X = 0; X < Width; X++)
		{
			CTile tile;

			if (fread(&tile.TileID, sizeof(tile.TileID), 1, FileHandle) == 0)
				return false;
			if (fread(&tile.TypeID, sizeof(tile.TypeID), 1, FileHandle) == 0)
				return false;
			if (fread(&tile.SwapTileID, sizeof(tile.SwapTileID), 1, FileHandle) == 0)
				return false;
			if (fread(&tile.SwapTypeID, sizeof(tile.SwapTypeID), 1, FileHandle) == 0)
				return false;

			tile.SetPos(X, Y);
			tile.SetTileset(Surf_Tileset);
			TileList.push_back(tile);
		}
	}

	if (fread(&StartX, sizeof(StartX), 1, FileHandle) == 0)
		return false;
	if (fread(&StartY, sizeof(StartY), 1, FileHandle) == 0)
		return false;

	fclose(FileHandle);

	return true;
}

void CMap::OnRender(SDL_Surface *Surf_Display, int MapX, int MapY)
{
    if (Surf_Tileset == NULL)
    	return;

	CSurface::FillRect(Surf_Display, 0, 0, CCamera::CameraControl.GetWindowSizeX(), CCamera::CameraControl.GetWindowSizeY(), BackColor);

	for (std::vector<CTile>::iterator i = TileList.begin(); i < TileList.end(); i++)
		i->OnRender(Surf_Display, MapX, MapY);
}

void CMap::OnCleanup()
{
    if (Surf_Tileset)
    {
        SDL_FreeSurface(Surf_Tileset);
        Surf_Tileset = NULL;
    }

    TileList.clear();
}

void CMap::OnLoop()
{
	for (std::vector<CTile>::iterator i = TileList.begin(); i < TileList.end(); i++)
		i->OnLoop();
}

CTile *CMap::GetTile(int X, int Y)
{
    unsigned int ID = X / TILE_SIZE + (Width * (Y / TILE_SIZE));

    if (ID < 0 || ID >= TileList.size())
        return NULL;

    return &TileList[ID];
}

void CMap::SetBackColor(char R, char G, char B)
{
	BackColor.r = R;
	BackColor.g = G;
	BackColor.b = B;
}
