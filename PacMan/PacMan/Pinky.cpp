#include "Pinky.h"

Pinky::Pinky()
{
	scatterTile = vec2(18, 1);
}

void Pinky::GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection)
{
	if (state == Scatter)
	{
		targetTile = scatterTile;
	}
	else
	{
		normalize(pacmanDirection);
		targetTile = pacmanTile + (4.0f * pacmanDirection);
	}
}

void Pinky::Update(vec2 pacmanTile, vec2 pacmanDirection)
{
	if (state == StandingInHouse)
	{
		if (time < 2000)
		{
			return;
		}
		else
		{
			state = Scatter;
			GetTargetTile(pacmanTile, pacmanDirection);
			time = 0;
		}
	}
	else if (state == Scatter)
	{
		if (mPosition.x == scatterTile.x * 10 + 5 && mPosition.z == scatterTile.y * 10 + 5)
		{
			state = Chase;
			time = 0;
		}
	}
	else if (state == Chase)
	{
		if (time < 20000)
		{
			GetTargetTile(pacmanTile, pacmanDirection);
		}
		else
		{
			state = Scatter;
			time = 0;
		}
	}
	else if (state == Frightened)
	{
		if (time < 5000)
		{
			//GetTargetTile(pacmanTile);
		}
		else
		{
			state = Chase;
			time = 0;
		}
	}
}