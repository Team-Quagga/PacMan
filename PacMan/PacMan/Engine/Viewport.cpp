#include "Viewport.h"

Viewport::Viewport(float _x, float _y, float _w, float _h) : x(_x), y(_y), width(_w), height(_h) {
	field_of_view = 45.0f;
	aspect_ratio = 1.0f;
	near = 0.1f;
	far = 250.0f;

	glGenFramebuffers(1, &frameBuffer);
};

Viewport::~Viewport() {
	glDeleteFramebuffers(1, &frameBuffer);
}

void Viewport::BuildProjectionMatrix(float _field_of_view, float _aspect_ratio, float _near, float _far) {
	if (_field_of_view) field_of_view = _field_of_view;
	if (_aspect_ratio) aspect_ratio = _aspect_ratio;
	if (_near) near = _near;
	if (_far) far = _far;


	projMatrix = glm::perspective(field_of_view, aspect_ratio, near, far);
}

using namespace glm;

glm::quat Viewport::BuildViewMatrix(vec3 _euler, vec3 _translation) {
	vec3 YAXIS(0, 1, 0);
	vec3 XAXIS(1, 0, 0);
	
	quat axis1 = angleAxis(_euler.y, YAXIS);
	quat axis2 = angleAxis(_euler.x, XAXIS);

	quat orientation = axis2 * axis1;
	mat3 rotmat = mat3_cast(orientation);

	viewMatrix = glm::toMat4(orientation);

	vec3 m_xAxis(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	vec3 m_yAxis(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
	vec3 m_zAxis(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);

	viewMatrix[3][0] = -dot(m_xAxis, _translation);
	viewMatrix[3][1] = -dot(m_yAxis, _translation);
	viewMatrix[3][2] = -dot(m_zAxis, _translation);

	return orientation;
}

void Viewport::SetRenderTarget() {
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}