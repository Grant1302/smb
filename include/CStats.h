/*
 * CStats.h
 *
 *  Created on: 05.10.2012
 *      Author: Anton L.
 */

#ifndef CSTATS_H_
#define CSTATS_H_

#include "CSurface.h"

class CStats
{
public:
	static CStats Stats;

public:
	int Level;
	int Lives;
	int Coins;
	unsigned int Score;

private:
	unsigned int Times[3];
	unsigned int Time;
    SDL_Surface *Surf_Score;
    int SavedCoins;
    int SavedScore;

public:
	void OnInit();
	bool OnRender(SDL_Surface *Surf_Display);
	void OnLoop();
	void SetTime(int Time);
	void Save();
	void Load();

private:
	CStats();
};

#endif /* CSTATS_H_ */
