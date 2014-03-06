#include "Player.h"


Player::Player(void)
{
	Player(glm::vec2(0,0));
}

Player::Player(glm::vec2 position)
{
	mPosition = position;
	mKeyPress = nullptr;
}

glm::vec2 Player::GetDirection()
{
	return mDirection;
}

Player::~Player(void)
{
}


void Player::SetKeyFunction(KeyPressFun f)
{
	mKeyPress = f;
}


glm::vec2 Player::GetPosition()
{
	return mPosition;
}

void Player::SetPosition(glm::vec2 nPosition)
{
	mPosition = nPosition;
}