#include <gl\glew.h>
#include "World.h"
#include <glm\glm.hpp>
#include "Blinky.h"
#include "Clyde.h"
#include "Inky.h"
#include "Pinky.h"


World::World(void)
{
}


World::~World(void)
{

}

bool World::LoadMap(const char* path)
{
	Blinky blinky;
	Clyde clyde;
	Inky inky;
	Pinky pinky;
	GLuint mapID = LoadBMP(path);

	bool superCandy;

	int ghostCounter = 0;
	for (int y = 0; y < 20 ; y++)
	{
		for (int x = 0; x < 20 ; x++)
		{
			if(colorData[x][y].b == 255 && colorData[x][y].g == 255 && colorData[x][y].r == 255)
			{
				map[x][y] = Tile(false, NULL, NULL);
			}
			if(colorData[x][y].b == 0 && colorData[x][y].g == 0 && colorData[x][y].r == 0)
			{
				map[x][y] = Tile(true, NULL, NULL);
			}
			else if(colorData[x][y].b == 255)
			{
				mPlayerPosXY[0] = x;
				mPlayerPosXY[1] = y;
				map[x][y] = Tile(false, NULL, NULL);
			}
			else if(colorData[x][y].g == 255)
			{
				Candy candy = Candy(x*y);
				candy.Init(glm::vec3(x * 10 + 5, 5, y * 10 + 5));
				map[x][y] = Tile(false, &candy, NULL);
			}
			else if(colorData[x][y].r == 255)
			{
				switch(ghostCounter)
				{
				case 0:
					map[x][y] = Tile(false,NULL,&blinky);
					ghostCounter++;
					break;
				case 1:
					map[x][y] = Tile(false,NULL,&clyde);
					ghostCounter++;
					break;
				case 2:
					map[x][y] = Tile(false,NULL,&inky);
					ghostCounter++;
					break;
				case 3:
					map[x][y] = Tile(false,NULL,&pinky);
					ghostCounter++;
					break;
				}
			}
			else
				printf("Kartan är ogiltig");
		}
	}

	CreateMapBuffer();
	return false;
}
void World::CreateMapBuffer()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			vertices.push_back(x*10);
			vertices.push_back(0);
			vertices.push_back(y*10);
			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(1);
			vertices.push_back(x/20);
			vertices.push_back(y/20);
			vertices.push_back(0);
			vertices.push_back(1);
			vertices.push_back(0);
		}
	}

	glGenBuffers(1, &vertexBuffer); //Generate one vertex object
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	mBatch = new Batch(new Material("None", "../../content/default_material.vs", "../../content/default_material.ps", NULL, NULL));

	mBatch->vertexBuffer = vertexBuffer;

	// Indexing
	std::vector<unsigned int> indices;

	int i = 0;
    for (int row=0; row<19; row++) 
	{
        if ( (row&1)==0 ) 
		{ // even rows
            for (int col=0; col<19; col++) 
			{
                indices.push_back(col + row * 19);
                indices.push_back(col + (row+1) * 19);
            }
        } else 
		{ // odd rows
            for (int col=19; col>0; col--) 
			{
                indices.push_back(col + (row+1) * 19);
                indices.push_back(col - 1 + + row * 19);
            }
        }
    }
	for (int i = 0; i < indices.size(); i++)
	{
		mBatch->elements.push_back(indices[i]);
	}

	mBatch->Load();
}
Tile* World::GetTile(int x, int y)
{
	return nullptr;
}
void World::Draw(glm::mat4 view, glm::mat4 projection)
{
	mBatch->Draw(&glm::mat4(1), &view, &projection);
}

GLuint World::LoadBMP(const char * imagepath)
{
	printf("Reading image %s\n", imagepath);

        // Data read from the header of the BMP file
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned int width, height;
        // Actual RGB data
        unsigned char* data;

        // Open the file
        FILE* file = fopen(imagepath,"rb");
        if (!file)                                                          
		{printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); return 0;}

        // Read the header, i.e. the 54 first bytes

        // If less than 54 bytes are read, problem
        if ( fread(header, 1, 54, file)!=54 ){ 
                printf("Not a correct BMP file\n");
                return 0;
        }
        // A BMP files always begins with "BM"
        if ( header[0]!='B' || header[1]!='M' ){
                printf("Not a correct BMP file\n");
                return 0;
        }
        // Make sure this is a 24bpp file
        if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
        if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

        // Read the information about the image
        dataPos    = *(int*)&(header[0x0A]);
        imageSize  = *(int*)&(header[0x22]);
        width      = *(int*)&(header[0x12]);
        height     = *(int*)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos==0)      dataPos=54; // The BMP header is done that way

        // Create a buffer
        data = new unsigned char[imageSize];

        // Read the actual data from the file into the buffer
        fread(data,1,imageSize,file);
		
		int k = 0;
		for(int x =0; x<width; x++)
		{
			for(int y = 0; y < height; y++)
			{
				colorData[x][y].x = data[k++];
				colorData[x][y].y = data[k++];
				colorData[x][y].z = data[k++];
			}
		}

        // Everything is in memory now, the file wan be closed
        fclose (file);

        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        
        // "Bind" the newly created texture : all future texture functions will modify this texture
        glActiveTexture(GL_TEXTURE0); // change active texture unit to number 0
		glBindTexture(GL_TEXTURE_2D, textureID); // bind the colorMap texture to the active texture unit (which is now 0)

        // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		
        // OpenGL has now copied the data. Free our own version
        delete [] data;

        // Poor filtering, or ...
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

        // ... nice trilinear filtering.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        glGenerateMipmap(GL_TEXTURE_2D);

        // Return the ID of the texture we just created
        return textureID;
}