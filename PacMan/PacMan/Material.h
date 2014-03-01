#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <GLFW/glfw3.h>

namespace glm {
	typedef glm::vec3 color;
};

class Material
{
public:
	Material(const char* _name, const char* _vs, const char* _ps, const char* _gs);
	~Material(void);

	void Load();
	const char* GetName() { return name; }
	void SetDiffuseColor(glm::color _color);

	GLuint shaderProgram;
private:
	Material(void);
	const char* name;
	glm::color diffuseColor;

	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;
};