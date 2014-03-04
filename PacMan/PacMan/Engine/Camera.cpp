#include "Camera.h"

Camera::Camera() {}

Camera::Camera(Viewport* _viewport) : viewport(_viewport) {
	viewport->BuildProjectionMatrix(NULL, NULL, NULL, NULL);
}

void Camera::Update() {
	if (refresh) {
		viewport->BuildViewMatrix(glm::eulerAngles(orientation), position);
		viewport->BuildProjectionMatrix(NULL, NULL, NULL, NULL);
	}
	refresh = false;
}

void Camera::SetOrientation(float pitch, float yaw) {
	orientation = glm::quat(glm::vec3(pitch, yaw, 0));
	refresh = true;
}

void Camera::SetPosition(glm::vec3 _pos) {
	position = _pos;
	refresh = true;
}

void Camera::Rotate(float degrees, glm::vec3& axis)
{
    if ( axis == glm::vec3(0.0f, 1.0f, 0.0f) )
        orientation =  glm::normalize(glm::angleAxis(degrees, axis)) * orientation;
    else
        orientation = orientation * glm::normalize(glm::angleAxis(degrees, axis));
	refresh = true;
}