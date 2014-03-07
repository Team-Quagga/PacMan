#include "Tile.h"


Tile::Tile(bool wall, Candy* candy, IGhost* ghost, float x, float y, Model* _model)
{
	mWall = wall;
	mCandy = candy;
	mGhost = ghost;

	if(mWall)
	{
		model = _model;
		//glm::translate(transformMatrix, glm::vec3(x, y, 0)); 
	}

	transformMatrix = glm::mat4(1);
	transformMatrix[3][0] = x;
	transformMatrix[3][2] = y;
}

void Tile::AddCandyModel(Model* _candyModel)
{
	candyModel = _candyModel;
}

Tile::~Tile(void)
{

}

void Tile::Draw(glm::mat4 view, glm::mat4 projection)
{
	if(mWall)
		model->Draw(&transformMatrix, &view, &projection);
	if(mCandy != NULL)
		candyModel->Draw(&transformMatrix, &view, &projection);
}

bool Tile::GetWalkable()
{
	return mWall;
}
