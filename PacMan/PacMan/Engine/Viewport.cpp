#include "Viewport.h"

void Viewport::BuildProjectionMatrix(float _field_of_view, float _aspect_ratio, float _near, float _far) {
	if (_field_of_view) field_of_view = _field_of_view;
	if (_aspect_ratio) aspect_ratio = _aspect_ratio;
	if (_near) near = _near;
	if (_far) far = _far;

	projMatrix[0][0] = 1.0f / (aspect_ratio * tan(field_of_view * 0.5f));
	projMatrix[1][1] = 1.0f / tan(field_of_view * 0.5f);
	projMatrix[2][2] = far / (far - near);
	projMatrix[2][3] = (-near * far) / (far - near);

	projMatrix[3][2] = 1.0f;
}

void Viewport::BuildViewMatrix(glm::vec3 _euler) {
	glm::detail::tvec3<mediump_float> YAXIS(0, 1, 0);
	glm::detail::tvec3<mediump_float> XAXIS(1, 0, 0);
	
	glm::detail::tquat<mediump_float> axis1 = angleAxis(_euler.y, YAXIS);
	glm::detail::tquat<mediump_float> axis2 = angleAxis(_euler.x, XAXIS);

	glm::detail::tquat<mediump_float> orientation = axis2 * axis1;
	glm::detail::tmat3x3<mediump_float> rotmat = mat3_cast(orientation);

	//TODO: apply rotmat to viewMatrix

	//Translation can be set later
}