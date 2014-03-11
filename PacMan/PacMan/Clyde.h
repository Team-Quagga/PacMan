#pragma once
#include "IGhost.h"

class Clyde:public IGhost
{
public:
	Clyde();
	void GetTargetTile(vec2 pacmanTile);
	void Update(vec2);
};