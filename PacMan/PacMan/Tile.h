#pragma once
#include "IGhost.h"
#include "Candy.h"
class Tile
{
	bool mWall;
	Candy* mCandy;
	IGhost* mGhost;
public:
	Tile(void);
	~Tile(void);
};

