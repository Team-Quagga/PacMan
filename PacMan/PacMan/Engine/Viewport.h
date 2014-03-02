#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Rect.h"

class Viewport {
public:
	Viewport(Rect _screen) : screen_rectangle(_screen) {
		field_of_view = 45.0f;
		aspect_ratio = 1.0f;
		near = 0.1f;
		far = 250.0f;
	};

	void BuildViewMatrix(glm::vec3 _euler, glm::vec3 _translation);
	void BuildProjectionMatrix(float _field_of_view, float _aspect_ratio, float _near, float _far);

	glm::mat4* GetViewMatrix() { return &viewMatrix; }
	glm::mat4* GetProjMatrix() { return &projMatrix; }

	Rect screen_rectangle;
private:
	Viewport(void);
	float field_of_view;
	float aspect_ratio;
	float near;
	float far;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};