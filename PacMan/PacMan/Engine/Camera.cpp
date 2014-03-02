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

void Camera::SetRotation(glm::vec3 _rot) {
	orientation = glm::quat(_rot);
	refresh = true;
}

void Camera::SetPosition(glm::vec3 _pos) {
	position = _pos;
	refresh = true;
}