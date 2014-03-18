#pragma once
#include "engine\input.h"
#include "Engine\Camera.h"
#include <glm\glm.hpp>
#include "Model.h"
#include "Tile.h"
#include "World.h"
class GameScreen;

class Player :
	public KeyObserver
{
	//KeyPressFun mKeyPress;
	Camera* mCamera;
	glm::vec2 mPosition;
	// Direction i grader och som vec2
	int mDirection;
	int cameraDirection;
	int cameraTargetDirection;
	int rotation;
	int mPrevDirection;
	glm::vec2 prefDirection;
	glm::vec2 direction;
	glm::vec2 targetTile;
	glm::vec2 prefTile;
	glm::vec3 cameraPosition;
	glm::vec2 tilePosition;
	bool invert;
	bool turnLeft;
	bool turnRight;
	Model playerModel;
	glm::mat4 transformMatrix;
	Tile* tempTile;
	World* mWorld;
	bool Walkable(glm::vec2);
public:
	Player();
	Player(Camera* camera, glm::vec2 position, World* world);
	~Player(void);
	void Update(GLFWwindow* mWindow, GameScreen* s);
	void DebugUpdate(GLFWwindow* mWindow, GameScreen* s);
	void SetKeyFunction(KeyPressFun f);
	glm::vec2 GetPosition();
	glm::vec2 GetDirection();
	void SetPosition(glm::vec2 position);
	void SetDirection(glm::vec2 direction);
	void Draw(glm::mat4 view, glm::mat4 projection);
	glm::vec2 GetTile();
};

