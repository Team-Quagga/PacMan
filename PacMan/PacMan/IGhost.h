#pragma once
#include "IGameObject.h"
#include "World.h"

enum GhostStates
{
	StandingInHouse,
	Chase,
	Frightened,
	Scatter
};

class IGhost:protected IGameObject
{
public:
	IGhost(){};
	virtual void Init(vec3 position);
	virtual void Draw(glm::mat4 view, glm::mat4 projection);
	void ChoseDirection();
	void Move();
	void SuperCandy();
	vec2 GetPosition();
	void GetTargetTile(vec2, vec2, vec2);
protected:
	bool active;
	GhostStates state;
	vec2 scatterTile;
	vec2 targetTile;
	vec2 nextTile; //New
	vec2 currentTile; //New
	int time; //New
	World* world;
	glm::mat4 transFormMatrix;
	void UpdateBase();
private:
	void TestTiles(vec2 preferedTile); //New
	int lastTime; //New
	bool Walkable(vec2 tile);
	vec2 prevTile;
};