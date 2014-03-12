#pragma once
#include "Candy.h"
#include "Model.h"
#include <glm\glm.hpp>

class IGhost;
class Tile
{
	Model* model;
	glm::mat4 transformMatrix;
public:
	Model* candyModel;
	IGhost* mGhost;
	Tile(void){};
	Tile(bool wall, Candy* candy, IGhost* ghost, float x, float y, float z, Model* _model);
	~Tile(void);
	void Draw(glm::mat4 view, glm::mat4 projection);
	bool GetWalkable();
	void AddCandyModel(Model* _candyModel);
	bool mWall;
	Candy* mCandy;
};

