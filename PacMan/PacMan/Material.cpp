#include "Engine\Engine.h"

#include "Material.h"

Material::Material(void) {}

Material::Material(const char* _name, const char* _vs, const char* _ps, const char* _gs) : name(_name)
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

void Material::SetShaderParams(glm::mat4* _worldMatrix, glm::mat4* _viewMatrix, glm::mat4* _projMatrix) {
	GLuint loc;

	loc = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(*_worldMatrix));

	loc = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(*_viewMatrix));

	loc = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(*_projMatrix));
}

void Material::SetDiffuseColor(glm::color _color) {
	//diffuseColor = _color;
}

Material::~Material(void)
{

}
