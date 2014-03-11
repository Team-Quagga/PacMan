#include "Clyde.h"

Clyde::Clyde()
{
	scatterTile = vec2(18, 18);
}

void Clyde::GetTargetTile(vec2 pacmanTile)
{
	if (state == Scatter)
	{
		targetTile = scatterTile;
	}
	else
	{
		vec2 distance = pacmanTile - currentTile;
 		if(distance.length() <= 8)
			targetTile = scatterTile;
		else
			targetTile = pacmanTile;

	}
}

void Clyde::Update(vec2 pacmanTile)
{
	if (state == StandingInHouse)
	{
		if (time < 10000)
		{
			return;
		}
		else
		{
			state = Scatter;
			GetTargetTile(pacmanTile);
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
			GetTargetTile(pacmanTile);
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
			GetTargetTile(pacmanTile);
		}
		else
		{
			state = Chase;
			time = 0;
		}
	}
}