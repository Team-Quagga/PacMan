#pragma once

#include "Batch.h"

using namespace std;

class Model
{
public:
	Model(void);
	~Model(void);

	void Load();
	void Draw();
	void Draw(glm::vec3* _pos, glm::vec3* _rot);
	void DrawSolid();
	void LoadFromFile(const char* path);
	Material* FindMaterial(const char* name);

private:
	std::vector<float> shared;
	std::vector<Batch*> batches;
	GLuint vertexArray;
	GLuint vertexBuffer;
};

