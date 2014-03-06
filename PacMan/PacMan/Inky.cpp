#include "Inky.h"

void Inky::GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection, vec2 blinkyTile)
{
	if (state == Scatter)
	{
		targetTile = scatterTile;
	}
	else
	{
		targetTile = pacmanTile;
	}
}

void Inky::Update(vec2 pacmanTile)
{
	if (state == StandingInHouse)
	{
		if (time < 3000)
		{
			return;
		}
		else
		{
			state = Scatter;
			//GetTargetTile(pacmanTile);
			time = 0;
		}
	}
	else if (state == Scatter)
	{
		if (mPosition.x == scatterTile.x * 10 + 5 && mPosition.y == scatterTile.y * 10 + 5)
		{
			state = Chase;
			time = 0;
		}
	}
	else if (state == Chase)
	{
		if (time < 20000)
		{
			//GetTargetTile(pacmanTile);
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