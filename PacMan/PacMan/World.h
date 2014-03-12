#pragma once
#include "Tile.h"
#include "Batch.h"
#include <glm\glm.hpp>


class World
{
	Tile* mMap;
	Batch* mBatch;
public:
	int mCandiesEaten;
	int mCandiesTotal;
	int mPlayerPosXY[2];
	int mGhostPosXY[2];
	World(void);
	~World(void);
	bool LoadMap(const char* path);
	static Tile* GetTile(int x, int y);
	void Draw(glm::mat4 view, glm::mat4 projection);
	GLuint LoadBMP(const char * imagepath);
	glm::vec3 colorData[20][20];
	Tile map[20][20];
	void CreateMapBuffer();
	GLuint vertexBuffer;
	std::vector<float> vertices; //do we need those?
	Material* mMaterial; //??
private:
	Model ghostModel;
	Model wallModel;
	Model groundModel;
	Model candyModel;
	Model mushroomsModel;
	Model candlesModel;
	Model gravestoneModel;
	struct random_prop {
		random_prop(glm::mat4* _transform, Model* _model) : transform(_transform), model(_model) {}
		Model* model;
		glm::mat4* transform;
	};
	std::vector<random_prop*> random_props;
	random_prop* AddRandomProp(Model*, float x, float y, float z, int probability);
};

