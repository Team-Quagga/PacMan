#include "Engine\Engine.h"
#include <fstream>

Model* Engine::LoadModel(const char* path)
{
	Model* tmp = new Model();
	tmp->LoadFromFile(path);
	return tmp;
}


char* Engine::ReadFile(const char* filename)
{
	ifstream fil;
	int fileSize;
	char input;
	char* buffer;

	fil.open(filename);

	if (fil.fail())
	{
		printf("not found? \n");
		return 0;
	}

	//Check file size
	fileSize = 0;
	fil.get(input);
	while (!fil.eof())
	{
		fileSize++;
		fil.get(input);
	}
	fil.close();

	
	buffer = new char[fileSize + 1];
	if (!buffer) return 0;


	//Fill the buffer by opening it again
	fil.open(filename);
	fil.read(buffer, fileSize);
	fil.close();
	buffer[fileSize] = '\0';

	return buffer;
}
