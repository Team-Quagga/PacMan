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
	void ResetParams();
	void SetDiffuseColor(glm::color _color);
	void SetDiffuseTexture(const char* _diffusePath);
	void SetSemiTransparent(bool _transparent);

	GLuint shaderProgram;
private:
	Material(void);
	bool transparent;
	const char* name;
	glm::color diffuseColor;
	GLuint diffuseTexture;
	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;
};