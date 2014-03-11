#pragma once
#include "engine\input.h"
#include "Engine\Camera.h"
#include <glm\glm.hpp>
class Player :
	public KeyObserver
{
	//KeyPressFun mKeyPress;
	Camera* mCamera;
	glm::vec2 mPosition;
	glm::vec2 mDirection;
public:
	Player(void);
	Player(glm::vec2 position);
	~Player(void);
	void Update(GLFWwindow* mWindow);
	void SetKeyFunction(KeyPressFun f);
	glm::vec2 GetPosition();
	glm::vec2 GetDirection();
	void SetPosition(glm::vec2 position);
	void SetDirection(glm::vec2 direction);
};

