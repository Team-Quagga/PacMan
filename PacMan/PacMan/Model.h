#pragma once

#include "Batch.h"
#include "Engine\Viewport.h"

using namespace std;

class Model
{
public:
	Model(void);
	~Model(void);

	void Load();
	void Draw();
	void Draw(glm::mat4* _modelMatrix, glm::mat4* _viewMatrix, glm::mat4* _projMatrix);
	void DrawSolid();
	void LoadFromFile(const char* path);
	Material* FindMaterial(const char* name);

private:
	std::vector<float> shared;
	std::vector<Batch*> batches;
	GLuint vertexArray;
	GLuint vertexBuffer;
};

