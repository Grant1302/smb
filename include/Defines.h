/*
 * Defines.h
 *
 *  Created on: Nov 30, 2012
 *      Author: Anton L.
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define TILE_SIZE 16

enum
{
    TILE_TYPE_NONE = 0,
    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK,
    TILE_TYPE_BUMPABLE,
    TILE_TYPE_BUMPABLECOIN,
    TILE_TYPE_COIN
};

#ifdef WIN32
#define PATH_FONT		"data\\fonts\\times.ttf"
#define PATH_LOGO		"data\\images\\logo.png"
#define PATH_SELECT		"data\\images\\select.png"
#define PATH_MARIO		"data\\images\\mario.png"
#define PATH_SCORE		"data\\images\\score.png"
#define PATH_COIN		"data\\images\\coin.png"
#define PATH_LEVEL1		"data\\maps\\level1.map"
#define PATH_TILESETS	"data\\tilesets\\"
#else
#define PATH_FONT		"data/fonts/times.ttf"
#define PATH_LOGO		"data/images/logo.png"
#define PATH_SELECT		"data/images/select.png"
#define PATH_MARIO		"data/images/mario.png"
#define PATH_SCORE		"data/images/score.png"
#define PATH_COIN		"data/images/coin.png"
#define PATH_LEVEL1		"data/maps/level1.map"
#define PATH_TILESETS	"data/tilesets/"
#endif

#endif /* DEFINES_H_ */
