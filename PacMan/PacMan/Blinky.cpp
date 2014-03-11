#include "Blinky.h"

Blinky::Blinky(World* _world)
{
	scatterTile = vec2(1, 1);
	world = _world;
}

void Blinky::GetTargetTile(vec2 pacmanTile)
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

void Blinky::Update(vec2 pacmanTile)
{
	if (state == StandingInHouse)
	{
		if (time < 1000)
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