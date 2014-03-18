#pragma once
#include "Tile.h"
#include "Batch.h"
#include "AudioSource.h"
#include "AudioEngine.h"
#include <glm\glm.hpp>


class Blinky;
class Clyde;
class Inky;
class Pinky;
class Player;
class Camera;
class GameScreen;

class World
{
	AudioStream* mCandySound;

	Tile* mMap;
	Batch* mBatch;
	Player* pacman;
	Camera* camera;
	Blinky* blinky;
	Clyde* clyde;
	Inky* inky;
	Pinky* pinky;
public:
	AudioEngine* mAEngine;
	int mCandiesEaten;
	int mCandiesTotal;
	int mPlayerPosXY[2];
	int mGhostPosXY[2];
	World(Camera* camera);
	World(){};
	~World(void);
	bool LoadMap(const char* path);
	Tile* GetTile(int x, int y);
	void Update(GLFWwindow* window, GameScreen* s);
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

