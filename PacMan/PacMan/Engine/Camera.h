#pragma once
#include "Viewport.h"

class Camera {
public:
	glm::vec3 rotation;
	glm::quat orientation;
	glm::vec3 position;

	Camera();
	Camera(Viewport*);

	void Update();
	void SetOrientation(float pitch, float yaw);
	void LookAt(glm::vec3 _world_pos);
	void SetPosition(glm::vec3 _pos);

	glm::mat4* GetViewMatrix() { return viewport->GetViewMatrix(); }
	glm::mat4* GetProjMatrix() { return viewport->GetProjMatrix(); }

	Viewport* GetViewport() { return viewport; }

private:
	bool refresh;
	Viewport* viewport;
};