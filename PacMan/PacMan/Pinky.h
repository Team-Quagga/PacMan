#pragma once
#include "IGhost.h"

class Pinky:public IGhost
{
public:
	void GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection);
};