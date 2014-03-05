#include "IGhost.h"

class Inky:public IGhost
{
public:
	void GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection, vec2 blinkyTile);
};