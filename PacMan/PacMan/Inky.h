#pragma once
#include "IGhost.h"

class Inky:public IGhost
{
public:
	Inky():IGhost()
	{};
	void GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection, vec2 blinkyTile);
};