#include "Player.h"
#include <iostream>
#include "World.h"
#include <math.h>

Player::Player()
{
	//Player(nullptr, glm::vec2(0,0));
}

Player::Player(Camera* camera, glm::vec2 position, World* world)
{
	mCamera = camera;
	mDirection = 0;
	mPosition = position;
	invert = false;
	transformMatrix = glm::mat4(1);
	playerModel.LoadFromFile("../../content/blender_suzanne.obj", 0.3);
	playerModel.Load();
	tilePosition = position;
	targetTile = mPosition;
	direction = glm::vec2(1,0);
	mWorld = world;

	mKeyPress = [&](GLFWwindow* w, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(w,  GLFW_KEY_DOWN ) == GLFW_PRESS)
		{
			//position += forward * deltaTime;
			invert = true;//TODO: troligen skum :/
		}
		if (glfwGetKey(w,  GLFW_KEY_LEFT ) == GLFW_PRESS)
		{
			turnLeft = true;
		}
		if (glfwGetKey(w,  GLFW_KEY_RIGHT ) == GLFW_PRESS)
		{
			turnRight = true;
		}
	};
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
	
	//Move forward
	if (glfwGetKey(mWindow,  GLFW_KEY_W ) == GLFW_PRESS)
	{
	//TODO kollision mot världen så man går rätt 
		position -= forward * deltaTime;
	}
	// Move backward
	//if (glfwGetKey(mWindow,  GLFW_KEY_S ) == GLFW_PRESS)
	//{
	//	//position += forward * deltaTime;
	//	horizontalAngle *= -1;
	if(invert)
	{
		invert = false;
		horizontalAngle -= 180;
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

void Player::DebugUpdate(GLFWwindow* mWindow)
{
	// Starting values
	static float horizontalAngle;
	static float verticalAngle;

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
	glm::vec3 cameraPosition = mCamera->position;
	
	// Camera
	if (glfwGetKey(mWindow,  GLFW_KEY_W ) == GLFW_PRESS)
	{
		cameraPosition -= forward * deltaTime;
	}
	if (glfwGetKey(mWindow,  GLFW_KEY_A ) == GLFW_PRESS)
	{
		cameraPosition -= strafe * deltaTime;
	}
	if (glfwGetKey(mWindow,  GLFW_KEY_D ) == GLFW_PRESS)
	{
		cameraPosition += strafe * deltaTime;
	}
	if (glfwGetKey(mWindow,  GLFW_KEY_S ) == GLFW_PRESS)
	{
		cameraPosition += forward * deltaTime;
	}

	mPrevDirection = mDirection;

		// Player
		if(invert)
		{
			invert = false;
			mDirection -= 180;
		}
		if (turnLeft)
		{
			turnLeft = false;
			mDirection -= 90;
		}
		if (turnRight)
		{
			turnRight = false;
			mDirection += 90;
		}

	//std::cout<<mDirection<<std::endl;

	if(mDirection < 0)
		mDirection += 360;
	if(mDirection >= 360)
		mDirection -= 360;

	if(mDirection == 0)
		prefDirection = glm::vec2(1,0);
	if(mDirection == 90)
		prefDirection = glm::vec2(0,1);
	if(mDirection == 180)
		prefDirection = glm::vec2(-1,0);
	if(mDirection == 270)
		prefDirection = glm::vec2(0,-1);

	//std::cout<<direction.x<<","<<direction.y<<std::endl;


	if(std::abs((mPosition.x - targetTile.x)) < 0.02 && std::abs((mPosition.y - targetTile.y)) < 0.02)
	{
		mPosition = targetTile;
		prefTile = mPosition + prefDirection;
		if(Walkable(prefTile))
		{
			targetTile = prefTile;
			direction = prefDirection;
		}
		if(Walkable(mPosition + direction))
			targetTile = mPosition + direction;
	}	

	if(Walkable(targetTile))
	{
		mPosition = glm::vec2(mPosition.x + direction.x * 0.01, mPosition.y + direction.y * 0.01);
	}
	

	/*tempTile = mWorld->GetTile(mPosition.x + (targetTile.x - mPosition.x), mPosition.y + direction.y);

	if(tempTile->mWall)
	{
		direction = prevDirection;
		mDirection = mPrevDirection;
	}
	else
	{
		mPosition = glm::vec2(mPosition.x + direction.x * 0.01, mPosition.y + direction.y * 0.01);
	}*/

	transformMatrix[3][0] = mPosition.x;
	transformMatrix[3][2] = mPosition.y;

	mCamera->SetPosition(cameraPosition);
	mCamera->SetOrientation(verticalAngle, horizontalAngle);

	

	//mCamera->LookAt(glm::vec3(0, 0, 0)); Not working yet
		
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	mCamera->Update();
}

bool Player::Walkable(glm::vec2 tile)
{

	Tile* temp = mWorld->GetTile(tile.x, tile.y);
	if(temp->mWall)
		return false;

	return true;
}


void Player::Draw(glm::mat4 view, glm::mat4 projection)
{
	playerModel.Draw(&transformMatrix, &view, &projection);
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
	return direction;
}

void Player::SetPosition(glm::vec2 position)
{
	mPosition = position;
}

void Player::SetDirection(glm::vec2 direction)
{
	direction = direction;
}