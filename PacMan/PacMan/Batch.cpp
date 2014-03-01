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

	material->Load();
}

void Batch::Draw(glm::vec3* _pos, glm::vec3* _rot) {
	glUseProgram(material->shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
}

Batch::~Batch(void)
{

}
