#pragma once
#include "Batch.h"
#include <glm\glm.hpp>
using namespace std;

class Model
{
public:
	Model(void);
	~Model(void);
	void Draw(glm::vec3 position, glm::vec3 orientation);
	void DrawSolid();
	void LoadFromFile(const char* path);
private:
	vector<Batch> batches;
};

