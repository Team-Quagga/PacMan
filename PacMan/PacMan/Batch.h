#pragma once
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "Material.h"
#include <vector>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Batch
{
public:
	Batch(void);
	~Batch(void);
	std::vector<Vertex> vertices;
private:
	GLuint elementBuffer;
	Material material;
	
	GLuint vertexBuffer;
};

