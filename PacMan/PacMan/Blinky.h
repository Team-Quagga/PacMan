#pragma once
#include "IGhost.h"

class Blinky:public IGhost
{
public:
	Blinky(World* _world);
	void GetTargetTile(vec2 pacmanTile);
	void Update(vec2 pacmanTile);
};