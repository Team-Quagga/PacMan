#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Rect.h"

using namespace glm;

class Viewport {
public:
	Viewport(Rect _screen) : screen_rectangle(_screen) {};

	void BuildViewMatrix(glm::vec3 _euler);
	void BuildProjectionMatrix(float _field_of_view, float _aspect_ratio, float _near, float _far);

	Rect screen_rectangle;
private:
	Viewport(void);
	float field_of_view;
	float aspect_ratio;
	float near;
	float far;
	mat4 viewMatrix;
	mat4 projMatrix;
};