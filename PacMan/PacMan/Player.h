#pragma once
#include "engine\input.h"
#include <glm\glm.hpp>
class Player :
	public KeyObserver
{
	//KeyPressFun mKeyPress;
	glm::vec2 mPosition;
	glm::vec2 mDirection;
public:
	Player(void);
	Player(glm::vec2 position);
	~Player(void);
	void SetKeyFunction(KeyPressFun f);
	glm::vec2 GetPosition();
	void SetPosition(glm::vec2 nPosition);
	glm::vec2 GetDirection();
};

