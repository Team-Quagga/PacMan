#include "Inky.h"

Inky::Inky()
{
	scatterTile = vec2(1, 18);
}

void Inky::GetTargetTile(vec2 pacmanTile, vec2 pacmanDirection, vec2 blinkyTile)
{
	if (state == Scatter)
	{
		targetTile = scatterTile;
	}
	else
	{
		vec2 blinkyTarget = pacmanTile + (2.0f * pacmanDirection);
		vec2 blinkyDirection = blinkyTarget - blinkyTile;
		targetTile = blinkyTile + (2.0f * blinkyDirection); //blinkyDirection ska INTE vara normalieserad!

	}
}

void Inky::Update(vec2 pacmanTile, vec2 pacmanDirection, vec2 blinkyTile)
{
	if (state == StandingInHouse)
	{
		if (time < 8000)
		{
			return;
		}
		else
		{
			state = Scatter;
			GetTargetTile(pacmanTile, pacmanDirection, blinkyTile);
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
			GetTargetTile(pacmanTile, pacmanDirection, blinkyTile);
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