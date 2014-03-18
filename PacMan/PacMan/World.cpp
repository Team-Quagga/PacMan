#include <ctime>
#include <gl\glew.h>
#include "World.h"
#include <glm\glm.hpp>
#include "Model.h"
#include "Blinky.h"
#include "Clyde.h"
#include "Inky.h"
#include "Pinky.h"
#include "Player.h"

World::World(Camera* _camera)
{
	camera = _camera;
}


World::~World(void)
{

}

bool World::LoadMap(const char* path)
{
	World::map;

	blinky = new Blinky(this);

	GLuint mapID = LoadBMP(path);
	mCandiesTotal = 0;
	mCandiesEaten = 0;

	

	bool superCandy;

	// Load cube
	wallModel.LoadFromFile("../../content/wall.obj", 1);
	wallModel.Load();

	// Load Ground
	groundModel.LoadFromFile("../../content/ground.obj", 1);
	groundModel.Load();

	// Load candy
	candyModel.LoadFromFile("../../content/cherry.obj", 0.1);
	candyModel.Load();
	mCandySound = new AudioStream();//new AudioSource(mAEngine, "WAVE/Sound.wav", glm::vec3(0,0,0));
	mCandySound->LoadAudioFile("WAVE/Sound.wav");

	// Random props
	srand(time(NULL));
		mushroomsModel.LoadFromFile("../../content/mushrooms.obj", 1);
		mushroomsModel.Load();

		candlesModel.LoadFromFile("../../content/candles.obj", 0.25);
		candlesModel.Load();

		gravestoneModel.LoadFromFile("../../content/gravestone.obj", 0.5);
		gravestoneModel.Load();

		ghostModel.LoadFromFile("../../content/ghost.obj", 0.2);
		ghostModel.Load();

	int ghostCounter = 0;
	for (int y = 0; y < 20 ; y++)
	{
		for (int x = 0; x < 20 ; x++)
		{
			if(colorData[x][y].b == 255 && colorData[x][y].g == 255 && colorData[x][y].r == 255)
			{
				map[x][y] = Tile(false, NULL, NULL, x, y, 0, &wallModel);
				random_prop* prop = AddRandomProp(&gravestoneModel, x, y, 0, 10);
				if (prop)random_props.push_back(prop);
				//printf(" ");
			}
			else if(colorData[x][y].b == 0 && colorData[x][y].g == 0 && colorData[x][y].r == 0)
			{
				map[x][y] = Tile(true, NULL, NULL, x, y, 0, &wallModel);
				random_prop* prop = AddRandomProp(&mushroomsModel, x, y, 0, 10);
				if (prop)random_props.push_back(prop);
				//printf("H");
			}
			else if(colorData[x][y].r == 255)
			{
				mPlayerPosXY[0] = x;
				mPlayerPosXY[1] = y;


				pacman = new Player(camera, glm::vec2(1,1), this);
				map[x][y] = Tile(false, NULL, NULL, x*1, y*1, 0, &wallModel);
				printf("C");

			}
			else if(colorData[x][y].g == 255)
			{
				Candy* candy = new Candy(x*y);
				candy->SetSound(new AudioSource(mAEngine, mCandySound, glm::vec3(x,0,y)));
				////candy.Init(glm::vec3(x * 0.5 + 5, 5, y * 0.5 + 5));
				mCandiesTotal++;
				map[x][y] = Tile(false, candy, NULL, x, y, 0.05, &wallModel);
				map[x][y].AddCandyModel(&candyModel);
				random_prop* prop = AddRandomProp(&candlesModel, x, y, 0, 10);
				if (prop)random_props.push_back(prop);
				//printf(".");
			}
			else if(colorData[x][y].b == 255)
			{
				//printf("G");
				switch(ghostCounter)
				{
				case 0:
					blinky->Init(glm::vec3(x, 0, y));
					map[x][y] = Tile(false,NULL,blinky, x*1, y*1, 0, &wallModel);
					ghostCounter++;
					break;
				case 1:
					map[x][y] = Tile(false,NULL,clyde, x*1, y*1, 0, &wallModel);
					ghostCounter++;
					break;
				case 2:
					map[x][y] = Tile(false,NULL,inky, x*1, y*1, 0, &wallModel);
					ghostCounter++;
					break;
				case 3:
					map[x][y] = Tile(false,NULL,pinky, x*1, y*1, 0, &wallModel);
					ghostCounter++;
					break;
				}
			}
			else
			{
				printf("Kartan är ogiltig");
				return false;
			}
		}
		//printf("\n");
	}
	/*
	for (int y = 0; y < 20 ; y++)
	{
		for (int x = 0; x < 20 ; x++)
		{
			if(map[x][y].mCandy != NULL)
				printf(".");
			else if(map[x][y].mGhost != NULL)
				printf("G");
			else if(map[x][y].mWall)
				printf("H");
			else
				printf(" ");
		}
		printf("\n");
	}

	Input::GetInstance()->Register(*pacman);

	return true;
	*/
	return true;
}

Tile* World::GetTile(int x, int y)
{
	return &map[x][y];
}

World::random_prop* World::AddRandomProp(Model* model, float x, float y, float z, int probability) {
	int random = (rand() % probability);
	if (random == 0) {
		glm::mat4* transform = new glm::mat4(1);
		(*transform)[3][0] = x;
		(*transform)[3][1] = z;
		(*transform)[3][2] = y;

		return new random_prop(transform, model);
	}
	else return NULL;
}

void World::Update(GLFWwindow* window, GameScreen* s)
{
	blinky->Update(pacman->GetPosition());

	pacman->Update(window, s);

}

void World::Draw(glm::mat4 view, glm::mat4 projection)
{
	//mBatch->Draw(&glm::mat4(1), &view, &projection);
	for(int y = 0; y < 20; y++)
	{
		for(int x = 0; x < 20; x++)
		{
			map[x][y].Draw(view, projection);
		}
	}

	blinky->Draw(view, projection);

	pacman->Draw(*camera->GetViewMatrix(), *camera->GetProjMatrix());
	//groundModel.Draw(&glm::mat4(1), &view, &projection);
	
	//Draw some random stuff
	for (int i = 0; i < random_props.size(); i++) {
		random_prop* prop = random_props.at(i);
		prop->model->Draw(prop->transform, &view, &projection);
	}
	
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