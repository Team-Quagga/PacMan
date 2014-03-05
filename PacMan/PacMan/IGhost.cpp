#include "IGhost.h"

void IGhost::Init(vec3 position) 
{
	mModel = *Engine::LoadModel("ghost.obj", 1);
	mPosition = position;
}

void IGhost::Draw()
{
	mModel.Draw();
}

void IGhost::ChoseDirection()
{
	vec2 direction = targetTile - currentTile;
	if (abs(direction.x) > abs(direction.y))
	{
		if (direction.x > 0)
		{
			World::GetTile(nextTile.x + 1, nextTile.y)->mWall;

		}
	}
}

void IGhost::Move()
{

}

void IGhost::Update()
{
	
	Move();
}