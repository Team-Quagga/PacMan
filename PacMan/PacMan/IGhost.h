#pragma once
#include "IGameObject.h"

enum GhostStates
{
	Chase,
	Frightened,
	Scatter
};

class IGhost:protected IGameObject
{
public:
	void Init(vec3 position);
	void Draw() override;
	void ChoseDirection();
	void Move();
	void Update();

	void GetTargetTile(vec2, vec2, vec2);
protected:
	bool active;
	GhostStates state;
	vec2 scatterTile;
	vec2 targetTile;
};