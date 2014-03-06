#include "GameScreen.h"

GameScreen::GameScreen(ScreenManager* manager, GLFWwindow* window)
	:IScreen(manager, window)
{
	//=============================
	//Graphics* graphics = Engine::GetGraphics(); //TODO: Fix link error that appear for some reason..
	//Model model = *Engine::LoadModel("../../../content/blender_sphere.obj", 0.1);
	int width, height;
	glfwGetWindowSize(window, &width, &height);// s�tt i engine

	mCamera = new Camera(new Viewport(0,0, width, height));
		Viewport* viewport = mCamera->GetViewport();
		viewport->BuildProjectionMatrix(60.0f, (float)width / (float)height, 0.1f, 250.0f);

		
	mCamera->SetOrientation(0, 0.1);
	mCamera->SetPosition(glm::vec3(0.0, 0.1, 0.5));

	mKeyPress = [&](GLFWwindow* w, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(w, true);
	};
	mModel = *Engine::LoadModel("../../content/blender_suzanne.obj", 0.1);
	LoadWorld("bilder/map1.bmp");
}


GameScreen::~GameScreen(void)
{
	delete mCamera;
}

void GameScreen::Draw()
{
	glEnable(GL_DEPTH_TEST);
	mModel.Draw(&glm::mat4(1), mCamera->GetViewMatrix(), mCamera->GetProjMatrix());
	mWorld.Draw(*mCamera->GetViewMatrix(), *mCamera->GetProjMatrix());
	glDisable(GL_DEPTH_TEST);
}

void GameScreen::Update()
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
	horizontalAngle -= (oxpos-xpos)*0.001;//float(1024/2 - xpos );
	verticalAngle   -= (oypos-ypos)*0.001;//float( 768/2 - ypos );


	
	// Reset mouse position for next frame
	glfwSetCursorPos(mWindow, 1280/2, 720/2);
	/*if(verticalAngle >= 3.14/2) verticalAngle = 3.14/2;
	if(verticalAngle <= -3.14/2) verticalAngle = -3.14/2;

	if(horizontalAngle < 0) horizontalAngle += 3.14;
	if(horizontalAngle > 3.14) horizontalAngle -= 3.14;*/

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	direction = glm::normalize(direction);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Forward vector
	glm::vec3 forward(direction.x, 0, direction.z);
	forward = glm::vec3(forward.x/forward.length(), 0, forward.z/forward.length());
	glm::vec3 position = mCamera->position;// get funktion


	// Move forward
	if (glfwGetKey(mWindow,  GLFW_KEY_W ) == GLFW_PRESS)
	{
		position -= forward * deltaTime;
	}
	// Move backward
	if (glfwGetKey(mWindow,  GLFW_KEY_S ) == GLFW_PRESS)
	{
		position += forward * deltaTime;
	}
	// Strafe right
	if (glfwGetKey(mWindow,  GLFW_KEY_A ) == GLFW_PRESS)
	{
		position += right * deltaTime;
	}
	// Strafe left
	if (glfwGetKey(mWindow,  GLFW_KEY_D ) == GLFW_PRESS)
	{
		position -= right * deltaTime;
	}

	mCamera->SetOrientation(verticalAngle,horizontalAngle);
	mCamera->SetPosition(position);

	printf("V - %f --- H -%f\n", verticalAngle, horizontalAngle);
	
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	mCamera->Update();
}


bool GameScreen::LoadWorld(const char* path)
{
	if(!mWorld.LoadMap(path))
		return false;

	mPlayer = Player(glm::vec2(mWorld.mPlayerPosXY[0],mWorld.mPlayerPosXY[1]));
	mPlayer.SetKeyFunction([&](GLFWwindow* w, int key, int scancode, int action, int mods)->void
	{
		if(!action == GLFW_PRESS)
			return;

		glm::vec2 nPosition = mPlayer.GetPosition();
		glm::vec2 direction; //= glm::vec2(mCamera.GetDirection().x, mCamera.GetDirection().z);
		glm::vec3 right3; //= glm::cross(mCamera.GetDirection(), glm::vec3(0,1,0));
		glm::vec2 right = glm::vec2(right3.x, right3.z);
		switch (key)
		{
		case GLFW_KEY_W:
			{
				nPosition += direction;
			}break;
		case GLFW_KEY_A:
			{
				nPosition -= right;
			}break;
		case GLFW_KEY_S:
			{
				nPosition -= direction;
			}break;
		case GLFW_KEY_D:
			{
				nPosition += right;
			}break;
		default:
			break;
		}
		//mWorld.GetTile(
	});


}