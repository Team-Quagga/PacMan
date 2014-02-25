#pragma once
#include <glm\glm.hpp>

using namespace glm;

class IGameObject
{
public: 
	
	virtual void Draw() = 0;
	virtual void Init(vec3 position, int difficulty) = 0;
protected:
	//Model
	//Sound
	vec3 position;
};