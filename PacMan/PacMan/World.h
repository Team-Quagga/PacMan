#pragma once
#include "Tile.h"
#include "Batch.h"
#include <glm\glm.hpp>


class Blinky;
class Clyde;
class Inky;
class Pinky;
class Player;
class Camera;

class World
{
	Tile* mMap;
	Batch* mBatch;
	Player* pacman;
	Camera* camera;
	Blinky* blinky;
	Clyde* clyde;
	Inky* inky;
	Pinky* pinky;
public:
	int mCandiesEaten;
	int mCandiesTotal;
	int mPlayerPosXY[2];
	int mGhostPosXY[2];
	World(Camera* camera);
	World(){};
	~World(void);
	bool LoadMap(const char* path);
	Tile* GetTile(int x, int y);
	void Update(GLFWwindow* window);
	void Draw(glm::mat4 view, glm::mat4 projection);
	GLuint LoadBMP(const char * imagepath);
	glm::vec3 colorData[20][20];
	Tile map[20][20];
	void CreateMapBuffer();
	GLuint vertexBuffer;
	std::vector<float> vertices;
	Material* mMaterial;
	Model wallModel;
	Model groundModel;
	Model candyModel;
};

