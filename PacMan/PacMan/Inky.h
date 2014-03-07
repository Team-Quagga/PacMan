#pragma once
#include "IGhost.h"

class Inky:public IGhost
{
public:
	Inky();
	void GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection, vec2 blinkyTile);
	void Update(vec2, vec2, vec2);
};