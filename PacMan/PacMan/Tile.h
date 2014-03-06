#pragma once
<<<<<<< HEAD
#include "Candy.h"

=======
//#include "IGhost.h"
#include "Candy.h"
>>>>>>> origin/master
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

