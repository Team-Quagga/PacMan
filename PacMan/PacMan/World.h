#pragma once
#include "Tile.h"
#include "Batch.h"
#include <glm\glm.hpp>
class World
{
	
	Tile* mMap;
	Batch mBatch;
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

};

