#pragma once
#include "Material.h"
#include <vector>


struct Vertex
{
	Vertex(glm::vec3 _pos, glm::vec2 _uv, glm::vec3 _normal) : pos(_pos), texCoord(_uv), normal(_normal) {}

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Batch
{
public:
	void Load();
	void Draw(glm::vec3* _pos, glm::vec3* _rot);
	Batch(void);
	Batch(Material*);
	~Batch(void);

	const char* GetName() { return material->GetName(); }

	int element_count;
	GLuint elementBuffer;
	GLuint vertexBuffer;
	std::vector<int> elements;
	Material* material;
};

