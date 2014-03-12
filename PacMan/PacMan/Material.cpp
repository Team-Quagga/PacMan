#include "Engine\Engine.h"

#include "Material.h"
#include <SOIL.h>

Material::Material(void) {}

Material::Material(const char* _name, const char* _vs, const char* _ps, const char* _gs, const char* _tex) : name(_name)
{
	const char* vertexShaderBuffer = Engine::ReadFile(_vs);
	const char* fragmentShaderBuffer = Engine::ReadFile(_ps);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Fill shader with our code
	glShaderSource(vertexShader, 1, &vertexShaderBuffer, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderBuffer, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//===================== Error check
	int status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != 1) printf("!! Vertex shader compile error !! \n");

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != 1) printf("!! Fragment shader compile error !! \n");
	//===================== /

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);

	if (_gs) {
		//TODO: Generate shader headers on the fly
		const char* geometryShaderBuffer = Engine::ReadFile(_gs);
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderBuffer, NULL);
		glCompileShader(geometryShader);

		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &status);
		if (status != 1) printf("!! Geometry shader compile error !! \n");

		glAttachShader(shaderProgram, geometryShader);
	}

	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != 1) printf("!! Shader link error !! \n");

	printf("\t - Shader initialized \n");
}

void Material::Load() {
	//====================== Define vertex data structure

	GLint posAttrib = glGetAttribLocation(shaderProgram, "inputPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "inputColor");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texCoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));

	GLint normAttrib = glGetAttribLocation(shaderProgram, "inputNormal");
	glEnableVertexAttribArray(normAttrib);
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	printf(" \t - MAT [%s] load complete \n", name);
}

void Material::Unload()
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "inputPosition");
	glDisableVertexAttribArray(posAttrib);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "inputColor");
	glDisableVertexAttribArray(colAttrib);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texCoord");
	glDisableVertexAttribArray(texAttrib);

	GLint normAttrib = glGetAttribLocation(shaderProgram, "inputNormal");
	glDisableVertexAttribArray(normAttrib);
}

void Material::SetShaderParams(glm::mat4* _worldMatrix, glm::mat4* _viewMatrix, glm::mat4* _projMatrix) {
	GLuint loc;

	//Load();//TESTFIX

	loc = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(loc, 1, false, &(*_worldMatrix)[0][0]);

	loc = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(loc, 1, false, &(*_viewMatrix)[0][0]);

	loc = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(loc, 1, false, &(*_projMatrix)[0][0]);

	loc = glGetAttribLocation(shaderProgram, "diffuseColor");
	glVertexAttrib3f(loc, diffuseColor.r, diffuseColor.g, diffuseColor.b);

	if(diffuseTexture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, diffuseTexture);

		loc = glGetUniformLocation(shaderProgram, "diffuseTexture");
		glUniform1f(loc, 0);

		if (transparent) {
			glEnable(GL_BLEND);
		}
	}
}

void Material::ResetParams() {
	if (transparent) {
		glDisable(GL_BLEND);
	}
}

void Material::SetDiffuseColor(glm::color _color) {
	diffuseColor = _color;
}

void Material::SetDiffuseTexture(const char* _diffusePath) {
	GLuint diffuseTexture;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &diffuseTexture);

	int width, height;
	diffuseTexture = SOIL_load_OGL_texture(_diffusePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
	if (!diffuseTexture) printf("error loading texture\n");
	//unsigned char* diffuseData = SOIL_load_image(_diffusePath, &width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, diffuseData);

	glBindTexture(GL_TEXTURE_2D, diffuseTexture);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Material::SetSemiTransparent(bool _transparent) {
	transparent = _transparent;
}

Material::~Material(void)
{

}
