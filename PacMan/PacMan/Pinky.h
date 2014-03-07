#pragma once
#include "IGhost.h"

class Pinky:public IGhost
{
public:
	Pinky();
	void GetTargetTile(vec2, vec2);
	void Update(vec2, vec2);
};