#include "IGhost.h"



void IGhost::Init(vec3 position) 
{
	//mModel = *Engine::LoadModel("blender_suzanne.obj", 1);
	mModel.LoadFromFile("../../content/ghost.obj", 0.5);
	mModel.Load();
	mPosition = position;
	time = 0;
	state = StandingInHouse;
	transFormMatrix = glm::mat4(1);
	transFormMatrix[3][0] = position.x;
	transFormMatrix[3][2] = position.z;
	currentTile = glm::vec2(position.x, position.z);
	nextTile = currentTile;
	prevTile = currentTile;
}

//vec2 IGhost::GetPosition()
//{
//	return currentTile;
//}

void IGhost::SuperCandy()
{
	state = Frightened;
	time = 0;
}


void IGhost::Draw(glm::mat4 view, glm::mat4 projection)
{
	mModel.Draw(&transFormMatrix, &view, &projection);
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
	vec2 tempTile = preferedTile;
	if(Walkable(tempTile) && tempTile != prevTile)
	{
		nextTile = tempTile;
		return;
	}
	tempTile = glm::vec2(currentTile.x - 1, currentTile.y);
	if(Walkable(tempTile) && tempTile != prevTile)
	{
		nextTile = tempTile;
		return;
	}
	tempTile = glm::vec2(currentTile.x + 1, currentTile.y);
	if(Walkable(tempTile) && tempTile != prevTile)
	{
		nextTile = tempTile;
		return;
	}
	tempTile = glm::vec2(currentTile.x, currentTile.y - 1);
	if(Walkable(tempTile) && tempTile != prevTile)
	{
		nextTile = tempTile;
		return;
	}
	tempTile = glm::vec2(currentTile.x, currentTile.y + 1);
	if(Walkable(tempTile) && tempTile != prevTile)
	{
		nextTile = tempTile;
		return;
	}
}

//Moves the ghost towards the next tile
void IGhost::Move()
{
	vec2 dir = nextTile - currentTile;
	mPosition.x += dir.x * 0.02;
	mPosition.z += dir.y * 0.02;

	transFormMatrix[3][0] = mPosition.x;
	transFormMatrix[3][2] = mPosition.z;

	Tile* current = world->GetTile(currentTile.x, currentTile.y);
	Tile* b = world->GetTile(mPosition.x, mPosition.z);
	if(current != b)
	{
		current->mGhost = nullptr;
		b->mGhost = this;
	}

}

bool IGhost::Walkable(vec2 tile)
{
	return world->GetTile(tile.x, tile.y)->GetWalkable();
}

vec2 IGhost::GetPosition()
{
	return currentTile;
}

//TODO
void IGhost::UpdateBase()
{
	time += glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	if (state == StandingInHouse)
		return;
	if (abs(mPosition.x - nextTile.x) < 0.02 && abs(mPosition.z - nextTile.y) < 0.02)
	{
		prevTile = currentTile;
		currentTile = nextTile;
		ChoseDirection();
	}
	Move();
}