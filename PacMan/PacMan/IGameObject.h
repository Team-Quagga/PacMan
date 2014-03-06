#pragma once
#include <glm\glm.hpp>
#include "Model.h"
#include "Engine\Engine.h"
#include "AudioSource.h"

using namespace glm;

class IGameObject
{
public: 
	virtual void Draw() = 0;
	virtual void Init(vec3 position) = 0;
protected:
	Model mModel;
	AudioSource* mSound;
	vec3 mPosition;
};