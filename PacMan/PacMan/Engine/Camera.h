#pragma once
#include "Viewport.h"

class Camera {
public:
	glm::quat orientation;
	glm::vec3 position;

	Camera();
	Camera(Viewport*);

	void Update();
	void SetRotation(glm::vec3 _rot);
	void SetPosition(glm::vec3 _pos);
	void Rotate(float degrees, glm::vec3& axis);// ej testad

	glm::mat4* GetViewMatrix() { return viewport->GetViewMatrix(); }
	glm::mat4* GetProjMatrix() { return viewport->GetProjMatrix(); }

	Viewport* GetViewport() { return viewport; }

private:
	bool refresh;
	Viewport* viewport;
};