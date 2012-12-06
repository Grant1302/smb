/*
 * CStats.cpp
 *
 *  Created on: 05.10.2012
 *      Author: Anton L.
 */

#include "CStats.h"
#include "CText.h"
#include "Defines.h"

CStats CStats::Stats;

CStats::CStats() :
	Level(0),
	Lives(0),
	Coins(0),
	Score(0),
	Time(0),
	Surf_Score(NULL),
	SavedCoins(0),
	SavedScore(0)
{
}

void CStats::OnInit()
{
    Surf_Score = CSurface::OnLoad(PATH_SCORE);
}

bool CStats::OnRender(SDL_Surface *Surf_Display)
{
	if (Surf_Display == NULL)
		return false;

	static char pscore[7] = "000000";
	char pscore2[7];
	char slevel[4] = "1-1";
	char scoins[5] = "x 00";
	static char stime[4] = "   ";
	int j;
	SDL_Color TextColor = { 255, 255, 255 };

	CText::OnRender(Surf_Display, 34, 1, "MARIO", TextColor);
	CText::OnRender(Surf_Display, 180, 1, "WORLD", TextColor);
	CText::OnRender(Surf_Display, 254, 1, "TIME", TextColor);

	strcpy(pscore, "000000");
	sprintf(pscore2, "%d", Score);
	j = 5;

	for (int i = strlen(pscore2) - 1; i >= 0; i--)
		pscore[j--] = pscore2[i];

	CText::OnRender(Surf_Display, 34, 9, pscore, TextColor);

	if (Times[1] != Times[2])
	{
		sprintf(stime, "%d", Times[0]);
		Times[2] = Times[1];
		Times[0]--;
		sprintf(stime, "%d", Times[0]);
	}
	CText::OnRender(Surf_Display, 260, 9, stime, TextColor);
	slevel[0] = (char)(Level / 5 + 1 - 208);
	slevel[2] = (char)(Level % 5 - 208);
	CText::OnRender(Surf_Display, 190, 9, slevel, TextColor);

	sprintf(scoins, "x %d", Coins);

	if (Coins < 10)
	{
		scoins[3] = scoins[2];
		scoins[2] = '0';
		scoins[4] = '\0';
	}

	CText::OnRender(Surf_Display, 108, 7, scoins, TextColor);
	CSurface::OnRender(Surf_Display, Surf_Score, 99, 8);

	return true;
}

void CStats::OnLoop()
{
	Time = SDL_GetTicks();
	Times[1] = Time / 1000;
}

void CStats::SetTime(int Time)
{
	Times[0] = Time;
	OnLoop();
	Times[2] = Times[1] - 1;
}

void CStats::Save()
{
	SavedCoins = Coins;
	SavedScore = Score;
}

void CStats::Load()
{
	Coins = SavedCoins;
	Score = SavedScore;
}
