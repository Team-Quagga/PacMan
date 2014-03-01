#include "Material.h"

Material::Material(void) {}

Material::Material(const char* _name, const char* _vs, const char* _ps, const char* _gs) : name(_name)
{

}

void Material::Load() {
	printf(" \t - MAT [%s] load complete \n", name);
}

void Material::SetDiffuseColor(glm::color _color) {

}

Material::~Material(void)
{

}
