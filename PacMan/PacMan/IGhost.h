#pragma once
#include "IGameObject.h"
#include "World.h"

enum GhostStates
{
	Chase,
	Frightened,
	Scatter
};

class IGhost:protected IGameObject
{
public:
	IGhost(){};
	virtual void Init(vec3 position);
	virtual void Draw();
	void ChoseDirection();
	void Move();
	void Update();

	void GetTargetTile(vec2, vec2, vec2);
protected:
	bool active;
	GhostStates state;
	vec2 scatterTile;
	vec2 targetTile;
	vec2 nextTile; //New
	vec2 currentTile; //New
private:
	void TestTiles(vec2 preferedTile); //New
};