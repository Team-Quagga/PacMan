#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GL\glew.h>
#include <GLFW/glfw3.h>

namespace glm {
	typedef glm::vec3 color;
};

class Material
{
public:
	Material(const char* _name, const char* _vs, const char* _ps, const char* _gs,const char* _tex);
	~Material(void);

	void Load();
	void Unload();
	const char* GetName() { return name; }
	void SetShaderParams(glm::mat4* _worldMatrix, glm::mat4* _viewMatrix, glm::mat4* _projMatrix);
	void SetDiffuseColor(glm::color _color);

	GLuint shaderProgram;
private:
	Material(void);
	const char* name;
	glm::color diffuseColor;
	const char* tex;
	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;
};