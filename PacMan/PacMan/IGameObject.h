#pragma once
#include <glm\glm.hpp>
#include "Model.h"
#include "Engine\Engine.h"

using namespace glm;

class IGameObject
{
public: 
	
	virtual void Draw() = 0;
	virtual void Init(vec3 position) = 0;
protected:
	Model mModel;
	//Sound
	vec3 mPosition;
};