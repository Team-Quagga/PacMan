#include "Tile.h"


Tile::Tile(bool wall, Candy* candy, IGhost* ghost)
{
	mWall = wall;
	mCandy = candy;
	mGhost = ghost;
}


Tile::~Tile(void)
{
}
