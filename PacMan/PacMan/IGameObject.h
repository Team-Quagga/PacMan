#pragma once
#include <glm\glm.hpp>

using namespace glm;

class IGameObject
{
public: 
	
	virtual void Draw() = 0;
	void Init(vec3 position);
protected:
	//Model
	//Sound
	vec3 position;
};