#pragma once
#include "Viewport.h"

using namespace glm;

class Camera {
public:
	quat orientation;
	vec3 poition;

	Camera();
	Camera(Viewport*);

	void Update();
	void SetRotation(glm::vec3 _rot);
	void SetPosition(glm::vec3 _pos);

	Viewport* GetViewport() { return viewport; }

private:
	bool refresh;
	Viewport* viewport;
};