#pragma once
#include "IGhost.h"

class Blinky:public IGhost
{
public:
	Blinky();
	void GetTargetTile(vec2 pacmanTile);
	void Update(vec2 pacmanTile);
};