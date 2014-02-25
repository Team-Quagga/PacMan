#pragma once
#include <GL\glew.h>
#include <fstream>
#include "Rect.h"
class Sprite: public Rect
{
	/*Rect
		float x, y, width, height;
		bool InterSect(Rect& r)(float x, float y);
		*/
public:
	enum FileFormat
	{
		TGA_TEXTURE,
		BMP_24BIT_TEXTURE
	};
	enum ColorFormat
	{
		NOT_SUPPORTED_COLOR,
		GRAY_COLOR = GL_RED,
		RGB_COLOR = GL_RGB,
		BGR_COLOR = GL_BGR,
		RGBA_COLOR = GL_RGBA,
		BGRA_COLOR = GL_BGRA
	};
//private:
	GLuint mTextureId;
	struct TexInfo
	{
		unsigned char imageTypeCode;
		short int imageWidth;
		short int imageHeight;
		unsigned char bitCount;
		unsigned char *imageData;
		ColorFormat imageColorType;
	} info;
	struct TexCoords
	{
		float a[2], b[2], c[2], d[2];
	} coords;

	bool LoadBMP(char * imagepath);
	bool LoadTGA(char *filename);
public:
	
	Sprite()
	{
		coords.a[0] = 0;
		coords.a[1] = 1;
		coords.b[0] = 0;
		coords.b[1] = 0;
		coords.c[0] = 1;
		coords.c[1] = 1;
		coords.d[0] = 1;
		coords.d[1] = 0;
	}
	virtual ~Sprite()
	{
	}

	bool LoadImange(char* filePath, FileFormat format);
	void SetTexCoords(float a[2], float b[2], float c[2], float d[2]);
	void Draw();//probably more params later
	void GenerateTexture();
	void BindTexture();
};

inline void Sprite::SetTexCoords(float a[2], float b[2], float c[2], float d[2])
{
	coords.a[0] = a[0];
	coords.a[1] = a[1];
	coords.b[0] = b[0];
	coords.b[1] = b[1];
	coords.c[0] = c[0];
	coords.c[1] = c[1];
	coords.d[0] = d[0];
	coords.d[1] = d[1];
}

inline void Sprite::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	// fixa parametrar som options sen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glLoadIdentity();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(coords.a[0], coords.a[1]);
	glVertex3f(x, y + height, 0);// up-left
	glTexCoord2f(coords.b[0], coords.b[1]);
	glVertex3f(x, y, 0);// down-left
	glTexCoord2f(coords.c[0], coords.c[1]);
	glVertex3f(x + width, y + height, 0);// up-right
	glTexCoord2f(coords.d[0], coords.d[1]);
	glVertex3f(x + width, y, 0);// down-rightS
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

inline void Sprite::GenerateTexture()
{
	glGenTextures(1, &mTextureId);
}

inline void Sprite::BindTexture()
{
	// "Bind" the newly created texture : all future texture functions will modify this texture       
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	// Give the image to OpenGL       
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.imageWidth, info.imageHeight, 0, info.imageColorType, GL_UNSIGNED_BYTE, info.imageData);
}

inline bool Sprite::LoadImange(char* filePath, Sprite::FileFormat format)
{
	switch (format)
	{
	case Sprite::TGA_TEXTURE:
		return LoadTGA(filePath);
		break;
	case Sprite::BMP_24BIT_TEXTURE:
		return LoadBMP(filePath);
		break;
	default:
		return false;
		break;
	}
}

inline bool Sprite::LoadBMP(char * imagepath)
{
	//printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file         
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;

	// Actual RGB data         
	unsigned char * data;

	// Open the file         
	FILE * file = fopen(imagepath, "rb");
	if (!file)
	{
		printf("%s could not be opened. Are you in the right directory?\n", imagepath);
		getchar();
		return false;
	}
	// Read the header, i.e. the 54 first bytes          
	// If less than 54 bytes are read, problem         
	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return false;
	}

	// A BMP files always begins with "BM"        
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return false;
	}
	// Make sure this is a 24bpp file    
	if (*(int*)&(header[0x1E]) != 0)
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return false;
	}
	if (*(int*)&(header[0x1C]) != 24)
	{
		printf("Not a correct BMP file\n");
		fclose(file);
		return false;
	}

	// Read the information about the image  
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	info.imageWidth = *(int*)&(header[0x12]);
	info.imageHeight = *(int*)&(header[0x16]); 
	info.bitCount = 3;
	info.imageTypeCode = 2;
	info.imageColorType = BGR_COLOR;
	// Some BMP files are misformatted, guess missing information     

	if (imageSize == 0)
		imageSize = width*height * info.bitCount;
	// 3 : one byte for each Red, Green and Blue component      
	if (dataPos == 0)
		dataPos = 54;
	// The BMP header is done that way    
	// Create a buffer     
	info.imageData = new unsigned char[imageSize];
	// Read the actual data from the file into the buffer 
	fread(info.imageData, 1, imageSize, file);
	// Everything is in memory now, the file wan be closed   
	fclose(file);          // Create one OpenGL texture    
	//GLuint textureID;
	//glGenTextures(1, &textureID);
	// "Bind" the newly created texture : all future texture functions will modify this texture       
	//glBindTexture(GL_TEXTURE_2D, textureID);
	// Give the image to OpenGL       
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	// OpenGL has now copied the data. Free our own version      
    
	

	return true;
}

inline bool Sprite::LoadTGA(char *filename)
{
	FILE *filePtr;
	unsigned char ucharBad;
	short int sintBad;
	long imageSize;
	int colorMode;
	unsigned char colorSwap;

	// Open the TGA file.
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
	{
		return false;
	}

	// Read the two first bytes we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// Which type of image gets stored in imageTypeCode.
	fread(&info.imageTypeCode, sizeof(unsigned char), 1, filePtr);

	// For our purposes, the type code should be 2 (uncompressed RGB image)
	// or 3 (uncompressed black-and-white images).
	if (info.imageTypeCode != 2 && info.imageTypeCode != 3)
	{
		fclose(filePtr);
		return false;
	}

	// Read 13 bytes of data we don't need.
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	// Read the image's width and height.
	fread(&info.imageWidth, sizeof(short int), 1, filePtr);
	fread(&info.imageHeight, sizeof(short int), 1, filePtr);

	// Read the bit depth.
	fread(&info.bitCount, sizeof(unsigned char), 1, filePtr);

	// Read one byte of data we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// Color mode -> 3 = BGR, 4 = BGRA.
	colorMode = info.bitCount / 8;
	info.imageColorType = (colorMode == 3) ? BGR_COLOR : (colorMode == 4) ? BGRA_COLOR : NOT_SUPPORTED_COLOR;
	imageSize = info.imageWidth * info.imageHeight * colorMode;

	// Allocate memory for the image data.
	info.imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

	// Read the image data.
	fread(info.imageData, sizeof(unsigned char), imageSize, filePtr);

	// Change from BGR to RGB so OpenGL can read the image data.
	/*for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = tgaFile->imageData[imageIdx];
		tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
		tgaFile->imageData[imageIdx + 2] = colorSwap;
	}*/

	fclose(filePtr);
	return true;
}
