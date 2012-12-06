/*
 * CScore.h
 *
 *  Created on: 04.10.2012
 *      Author: Anton L.
 */

#ifndef CSCORE_H_
#define CSCORE_H_

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include "Defines.h"
#include <vector>
#include <string>

class CScore
{
public:
	static std::vector<CScore> ScoreList;

private:
	int X, Y;
	bool Alive;
	float Offset;
	float Speed;
	std::string Text;

public:
	CScore();

public:
	void OnRender(SDL_Surface *Surf_Display);
	void OnLoop();
	void Spawn(int X, int Y, std::string Text);
	bool IsAlive();
};

#endif /* CSCORE_H_ */
