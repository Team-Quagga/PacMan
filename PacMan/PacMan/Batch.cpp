#include "Batch.h"

Batch::Batch(void) {}

Batch::Batch(Material* _material) {
	material = _material;
	element_count = 0;
}

void Batch::Load() {
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_count*sizeof(GLuint), &elements[0], GL_STATIC_DRAW);

	//Bind the necessary attributes for vertex shader to access
	glBindAttribLocation(material->shaderProgram, 0, "inputPosition");
	glBindAttribLocation(material->shaderProgram, 1, "inputColor");
	glBindAttribLocation(material->shaderProgram, 2, "texCoord");
	glBindAttribLocation(material->shaderProgram, 3, "inputNormal");

	material->Load();
}

void Batch::Draw(glm::mat4* _modelMatrix, glm::mat4* _viewMatrix, glm::mat4* _projMatrix) {
	material->SetShaderParams(_modelMatrix, _viewMatrix, _projMatrix);

	glUseProgram(material->shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
}

Batch::~Batch(void)
{

}
