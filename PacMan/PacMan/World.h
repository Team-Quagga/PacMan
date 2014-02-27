#pragma once
#include "Tile.h"
#include "Batch.h"
class World
{
	int mCandiesEaten;
	int mCandiesTotal;
	int mPlayerPosXY[2];
	int mGhostPosXY[2];
	Tile* mMap;
	Batch mBatch;
public:
	World(void);
	~World(void);
	bool LoadMap(const char* path);
	Tile* GetTile(int x, int y);
	void Draw(float view[16], float projection[16]);
};

