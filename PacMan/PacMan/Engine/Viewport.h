#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include "Rect.h"

class Viewport {
public:
	Viewport(float _x, float _y, float _w, float _h);
	~Viewport();

	void BuildViewMatrix(glm::vec3 _euler, glm::vec3 _translation);
	void BuildProjectionMatrix(float _field_of_view, float _aspect_ratio, float _near, float _far);

	glm::mat4* GetViewMatrix() { return &viewMatrix; }
	glm::mat4* GetProjMatrix() { return &projMatrix; }
	GLuint GetFrameBuffer() { return frameBuffer; }
	void SetRenderTarget();

	Rect screen_rectangle;
private:
	Viewport(void);
	
	float x, y, width, height;

	float field_of_view, aspect_ratio, near, far;

	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;

	GLuint frameBuffer;
};