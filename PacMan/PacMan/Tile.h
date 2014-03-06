#pragma once
#include "Candy.h"

class IGhost;
class Tile
{
	bool mWall;
	Candy* mCandy;
	IGhost* mGhost;
public:
	Tile(void){};
	Tile(bool wall, Candy* candy, IGhost* ghost);
	~Tile(void);
	bool GetWalkable();
};

