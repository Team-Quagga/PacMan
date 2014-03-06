#include "IGhost.h"

void IGhost::Init(vec3 position) 
{
	mModel = *Engine::LoadModel("ghost.obj", 1);
	mPosition = position;
	time = 0;
	state = StandingInHouse;
}

void IGhost::SuperCandy()
{
	state = Frightened;
	time = 0;
}

void IGhost::Draw()
{
	mModel.Draw();
}

//TODO: Test!
// Choses the next tile based on which is the closest walkable tile to the target tile, also makes sure that the next tile isn't the one it came from
void IGhost::ChoseDirection()
{
	vec2 direction;
	if (state == Frightened)
	{
		direction = currentTile - targetTile;
	}
	else
	{
		direction = targetTile - currentTile;
	}
	if (abs(direction.x) > abs(direction.y))
	{
		if (direction.x > 0)
		{
			TestTiles(vec2(nextTile.x + 1, nextTile.y));
		}
		else
		{
			TestTiles(vec2(nextTile.x - 1, nextTile.y));
		}
	}
	else
	{
		if (direction.y > 0)
		{
			TestTiles(vec2(nextTile.x, nextTile.y + 1));
		}
		else
		{
			TestTiles(vec2(nextTile.x, nextTile.y - 1));
		}
	}
}

void IGhost::TestTiles(vec2 preferedTile)
{
	if (World::GetTile(preferedTile.x, preferedTile.y)->GetWalkable() && (preferedTile.x != currentTile.x && preferedTile.y != currentTile.y))
	{
		currentTile = nextTile;
		nextTile = preferedTile;
	}
	else if (preferedTile.x == nextTile.x)
	{
		if (targetTile.y > nextTile.y)
		{
			if (World::GetTile(nextTile.x, nextTile.y + 1)->GetWalkable() && (nextTile.x != currentTile.x && nextTile.y + 1 != currentTile.y))
			{
				currentTile = nextTile;
				nextTile.y++;
			}
			else if (World::GetTile(nextTile.x, nextTile.y - 1)->GetWalkable() && (nextTile.x != currentTile.x && nextTile.y - 1 != currentTile.y))
			{
				currentTile = nextTile;
				nextTile.y--;
			}
		}
		else
		{
			if (World::GetTile(nextTile.x, nextTile.y - 1)->GetWalkable() && (nextTile.x != currentTile.x && nextTile.y - 1 != currentTile.y))
			{
				currentTile = nextTile;
				nextTile.y--;
			}
			else if (World::GetTile(nextTile.x, nextTile.y + 1)->GetWalkable() && (nextTile.x != currentTile.x && nextTile.y + 1 != currentTile.y))
			{
				currentTile = nextTile;
				nextTile.y++;
			}
		}
		
		if (currentTile.x > nextTile.x)
		{
			currentTile = nextTile;
			nextTile.x++;
		}
		else
		{
			currentTile = nextTile;
			nextTile.x--;
		}
	}
	else
	{
		if (World::GetTile(nextTile.x - 1, nextTile.y)->GetWalkable() && (nextTile.x - 1 != currentTile.x && nextTile.y != currentTile.y))
		{
			currentTile = nextTile;
			nextTile.x--;
		}
		else if (World::GetTile(nextTile.x + 1, nextTile.y)->GetWalkable() && (nextTile.x + 1 != currentTile.x && nextTile.y != currentTile.y))
		{
			currentTile = nextTile;
			nextTile.x++;
		}
		else if (currentTile.y > nextTile.y)
		{
			currentTile = nextTile;
			nextTile.y++;
		}
		else
		{
			currentTile = nextTile;
			nextTile.y--;
		}
	}
}

//Moves the ghost towards the next tile
void IGhost::Move()
{
	vec2 dir = nextTile - currentTile;
	mPosition.x += dir.x;
	mPosition.y += dir.y;
}

vec2 IGhost::GetPosition()
{
	return currentTile;
}

//TODO
void IGhost::Update()
{
	time += glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	if (state == StandingInHouse)
		return;
	if (mPosition.x == nextTile.x * 10 + 5 && mPosition.y == nextTile.y * 10 + 5)
		ChoseDirection();
	Move();
}