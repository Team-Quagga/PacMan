#include "Model.h"


Model::Model(void)
{
	batches.push_back(Batch());
}


Model::~Model(void)
{
}

void Model::LoadFromFile(const char* path)
{
	// Open the File
	FILE * file = fopen(path, "r");

	if( file == NULL ){
		printf("Could not open the .obj file!\n");
		return;
	}

	std::vector <glm::vec3> tempVertices;
	std::vector <glm::vec2> tempUvs;
	std::vector <glm::vec3> tempNormals;

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	// Read the file
	while( 1 )
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		/*else if (strcmp(lineHeader, "mtllib") == 0)
		{
			fscanf(file, "%s\n", matFilePath);
		}*/
		else if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tempUvs.push_back(uv);
		}
		else if (strcmp( lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if ( strcmp(lineHeader, "f") == 0) // Get correct indices
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File could not be red, all 9 matches could not be found");
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	// Indexing
	for( unsigned int i=0; i<vertexIndices.size(); i++ )
	{
		Vertex vertices;
		unsigned int Index = vertexIndices[i];
		glm::vec3 vertex = tempVertices[Index-1];
		

		Index = uvIndices[i];
		glm::vec2 uv = tempUvs[Index-1];
		//out_uvs.push_back(uv);

		Index = normalIndices[i];
		glm::vec3 normal = tempNormals[Index-1];
		//out_normals.push_back(normal);

		//batches[0].vertices.push_back();
	}
}
