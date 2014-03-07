#include "Pinky.h"

void Pinky::GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection)
{
	normalize(pacmanDirection);
	targetTile = pacmanTile + (4.0f * pacmanDirection);
}