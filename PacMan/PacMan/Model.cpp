#include "Model.h"


Model::Model(void) {}


Model::~Model(void) {
	for (int i = 0; i < batches.size(); i++) delete batches[i];
}

void Model::Load() {
	glGenVertexArrays(1, &vertexArray); // Generate one vertex array
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer); //Generate one vertex object
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, shared.size() * sizeof(float), &shared[0], GL_STATIC_DRAW);

	for (int i = 0; i < batches.size(); i++) batches.at(i)->Load();
	printf("> Model load complete \n");
}

void Model::Draw() {
	glBindVertexArray(vertexArray);

	Draw(NULL, NULL);
}

void Model::Draw(glm::vec3* _pos, glm::vec3* _rot) {
	for (int i = 0; i < batches.size(); i++) batches.at(i)->Draw(_pos, _rot);
}

void Model::LoadFromFile(const char* path)
{
	// Open the .obj file
	FILE* obj = fopen(path, "r");
	FILE* mtl = NULL;


	if (obj == NULL){
		printf("Could not open the .obj file!\n");
		return;
	}


	std::vector <glm::vec3> tempVertices;
	std::vector <glm::vec2>* tempUvs = NULL;
	std::vector <glm::vec3>* tempNormals = NULL;
	Batch* current = NULL;

	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;

	// Read the obj file
	while (obj)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(obj, "%s", lineHeader);
		if (res == EOF) break; // EOF = End Of File.Quit the loop.

		if (strcmp(lineHeader, "mtllib") == 0)
		{
			char* matFilePath = (char*)malloc(128);
			fscanf(obj, "%s\n", matFilePath);

			//TODO: make path relative to .obj
			mtl = fopen(matFilePath, "r");
		}
		if (strcmp(lineHeader, "usemtl") == 0)
		{
			char* matName = (char*)malloc(128);
			fscanf(obj, "%s\n", matName);

			//Material switch
			Batch* tmp = new Batch(new Material(matName, "../../../content/default_material.vs", "../../../content/default_material.ps", NULL));
			tmp->vertexBuffer = vertexBuffer;
			batches.push_back(tmp);
			current = tmp;
		}
		else if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(obj, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			if (!tempUvs) tempUvs = new std::vector <glm::vec2>();

			glm::vec2 uv;
			fscanf(obj, "%f %f\n", &uv.x, &uv.y);
			tempUvs->push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			if (!tempNormals) tempNormals = new std::vector <glm::vec3>();

			glm::vec3 normal;
			fscanf(obj, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals->push_back(normal);
		}


		else if (strcmp(lineHeader, "f") == 0) {
			bool quad = false;
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], deferredIndex[4], matches;
			unsigned int* uvIndex;
			unsigned int* normalIndex;

			if (!tempNormals && !tempUvs) {
				matches = fscanf(obj, "%i %i %i %i\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);
			}
			if (tempNormals && tempUvs) {
				uvIndex = new unsigned int[4];
				normalIndex = new unsigned int[4];
				matches = fscanf(obj, "%i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			}
			else if (tempNormals || tempUvs) {
				matches = fscanf(obj, "%i/%i %i/%i %i/%i %i/%i\n", &vertexIndex[0], &deferredIndex[0], &vertexIndex[1], &deferredIndex[1], &vertexIndex[2], &deferredIndex[2], &vertexIndex[3], &deferredIndex[3]);
				if (tempNormals) normalIndex = deferredIndex;
				if (tempUvs) uvIndex = deferredIndex;
			}

			if (matches == 4 || matches == 8 || matches == 12) quad = true;

			//Fill the temporary triangle/quad buffer before sending to GPU
			for (int v = 0; v < 2 + quad; v++) {
				glm::vec3 pos = tempVertices[vertexIndex[v]-1];
				glm::vec2 uv;
				glm::vec3 norm;
				if (tempUvs) uv = tempUvs->at(uvIndex[v] - 1);
				if (tempNormals) norm = tempNormals->at(uvIndex[v] - 1);

				shared.push_back(pos.x);
				shared.push_back(pos.y);
				shared.push_back(pos.z);

				shared.push_back(uv.x);
				shared.push_back(uv.y);
				
				shared.push_back(norm.x);
				shared.push_back(norm.y);
				shared.push_back(norm.z);

				current->element_count++;
				current->elements.push_back(vertexIndex[v]);
			}
		}
	}
	
	//Read the mtl file
	Material* current_material = NULL;
	while (mtl)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(mtl, "%s", lineHeader);
		if (res == EOF) break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "newmtl") == 0)
		{
			char* matName = (char*)malloc(128);
			fscanf(obj, "%s\n", matName);

			current_material = FindMaterial(matName);
		}
		if (strcmp(lineHeader, "Kd") == 0) {
			glm::color color;
			fscanf(obj, "%f %f %f\n", &color.x, &color.y, &color.z);

			current_material->SetDiffuseColor(color);
		}
	}

	printf("> OBJ load complete \n");
	Load();
}

Material* Model::FindMaterial(const char* name) {
	for (int c = 0; c < batches.size() - 1; c++) {
		if (strcmp(batches.at(c)->GetName(), name) == 0) {
			return batches.at(c)->material;
		}
	}
	return NULL;
}