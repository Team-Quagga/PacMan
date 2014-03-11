#include "Player.h"


Player::Player()
{
	Player(nullptr, glm::vec2(0,0));
}

Player::Player(Camera* camera, glm::vec2 position)
{
	mCamera = camera;
	mPosition = position;
	invert = false;
	mKeyPress = [&](GLFWwindow* w, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(w,  GLFW_KEY_S ) == GLFW_PRESS)
		{
			//position += forward * deltaTime;
			invert = true;//TODO: troligen skum :/
		}
	};
}

glm::vec2 Player::GetDirection()
{
	return mDirection;
}

Player::~Player(void)
{
}

void Player::Update(GLFWwindow* mWindow)
{
	static float horizontalAngle;
	// Initial vertical angle : none
	static float verticalAngle;
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	static double oxpos = 1280/2, oypos = 720/2;
	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);


	// Compute new orientation
	horizontalAngle -= (oxpos-xpos)*0.1;//float(1024/2 - xpos );
	verticalAngle   -= (oypos-ypos)*0.1;//float( 768/2 - ypos );


	mCamera->Update();
	// Reset mouse position for next frame
	glfwSetCursorPos(mWindow, 1280/2, 720/2);
	if (verticalAngle > 90.0 / 2) verticalAngle = 90.0 / 2;
	if (verticalAngle < -90.0 / 2) verticalAngle = -90.0 / 2;

	glm::vec3 forward = glm::vec3(0, 0, 1) * mCamera->orientation;
	glm::vec3 strafe = glm::vec3(1, 0, 0) * mCamera->orientation;
	glm::vec3 position = mCamera->position;
	
	// Move forward
	//if (glfwGetKey(mWindow,  GLFW_KEY_W ) == GLFW_PRESS)
	//{
	//TODO kollision mot världen så man går rätt 
		position -= forward * deltaTime;
	//}
	// Move backward
	//if (glfwGetKey(mWindow,  GLFW_KEY_S ) == GLFW_PRESS)
	//{
	//	//position += forward * deltaTime;
	//	horizontalAngle *= -1;
	if(invert)
	{
		invert = false;
		horizontalAngle *= -1;
	}
	//}
	// Strafe right
	if (glfwGetKey(mWindow,  GLFW_KEY_A ) == GLFW_PRESS)
	{
		position -= strafe * deltaTime;
	}
	// Strafe left
	if (glfwGetKey(mWindow,  GLFW_KEY_D ) == GLFW_PRESS)
	{
		position += strafe * deltaTime;
	}

	mCamera->SetPosition(position);
	mPosition = glm::vec2(position.x, position.z);
	mCamera->SetOrientation(verticalAngle, horizontalAngle);
	//mCamera->LookAt(glm::vec3(0, 0, 0)); Not working yet
		
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	mCamera->Update();
}

void Player::SetKeyFunction(KeyPressFun f)
{
	mKeyPress = f;
}


glm::vec2 Player::GetPosition()
{
	return mPosition;
}

glm::vec2 Player::GetDirection()
{
	return mDirection;
}

void Player::SetPosition(glm::vec2 position)
{
	mPosition = position;
}

void Player::SetDirection(glm::vec2 direction)
{
	mDirection = direction;
}