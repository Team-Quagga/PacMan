#pragma once
#include "GLHeader.h"
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
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	// fixa parametrar som options sen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glLoadIdentity();
	//glColor3f(0, 0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(coords.a[0], coords.a[1]);
	glVertex3f(x, y + height, -1);// up-left
	glTexCoord2f(coords.b[0], coords.b[1]);
	glVertex3f(x, y, -1);// down-left
	glTexCoord2f(coords.c[0], coords.c[1]);
	glVertex3f(x + width, y + height, -1);// up-right
	glTexCoord2f(coords.d[0], coords.d[1]);
	glVertex3f(x + width, y, -1);// down-rightS
	glEnd();

	glDisable(GL_BLEND);
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

//GLubyte *textureImage;
//float rotateX = 0;
//float rotateY = 0;
//
//int mouseX;
//int mouseY;
//
//bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
//    png_structp png_ptr;
//    png_infop info_ptr;
//    unsigned int sig_read = 0;
//    int color_type, interlace_type;
//    FILE *fp;
//    
//    if ((fp = fopen(name, "rb")) == NULL)
//        return false;
//    
//    /* Create and initialize the png_struct
//     * with the desired error handler
//     * functions.  If you want to use the
//     * default stderr and longjump method,
//     * you can supply NULL for the last
//     * three parameters.  We also supply the
//     * the compiler header file version, so
//     * that we know if the application
//     * was compiled with a compatible version
//     * of the library.  REQUIRED
//     */
//    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
//                                     NULL, NULL, NULL);
//    
//    if (png_ptr == NULL) {
//        fclose(fp);
//        return false;
//    }
//    
//    /* Allocate/initialize the memory
//     * for image information.  REQUIRED. */
//    info_ptr = png_create_info_struct(png_ptr);
//    if (info_ptr == NULL) {
//        fclose(fp);
//        png_destroy_read_struct(&png_ptr, NULL, NULL);
//        return false;
//    }
//    
//    /* Set error handling if you are
//     * using the setjmp/longjmp method
//     * (this is the normal method of
//     * doing things with libpng).
//     * REQUIRED unless you  set up
//     * your own error handlers in
//     * the png_create_read_struct()
//     * earlier.
//     */
//    if (setjmp(png_jmpbuf(png_ptr))) {
//        /* Free all of the memory associated
//         * with the png_ptr and info_ptr */
//        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
//        fclose(fp);
//        /* If we get here, we had a
//         * problem reading the file */
//        return false;
//    }
//    
//    /* Set up the output control if
//     * you are using standard C streams */
//    png_init_io(png_ptr, fp);
//    
//    /* If we have already
//     * read some of the signature */
//    png_set_sig_bytes(png_ptr, sig_read);
//    
//    /*
//     * If you have enough memory to read
//     * in the entire image at once, and
//     * you need to specify only
//     * transforms that can be controlled
//     * with one of the PNG_TRANSFORM_*
//     * bits (this presently excludes
//     * dithering, filling, setting
//     * background, and doing gamma
//     * adjustment), then you can read the
//     * entire image (including pixels)
//     * into the info structure with this
//     * call
//     *
//     * PNG_TRANSFORM_STRIP_16 |
//     * PNG_TRANSFORM_PACKING  forces 8 bit
//     * PNG_TRANSFORM_EXPAND forces to
//     *  expand a palette into RGB
//     */
//    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
//    
//    png_uint_32 width, height;
//    int bit_depth;
//    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
//                 &interlace_type, NULL, NULL);
//    outWidth = width;
//    outHeight = height;
//    
//    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
//    *outData = (unsigned char*) malloc(row_bytes * outHeight);
//    
//    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
//    
//    for (int i = 0; i < outHeight; i++) {
//        // note that png is ordered top to
//        // bottom, but OpenGL expect it bottom to top
//        // so the order or swapped
//        memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
//    }
//    
//    /* Clean up after the read,
//     * and free any memory allocated */
//    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
//    
//    /* Close the file */
//    fclose(fp);
//    
//    /* That's it */
//    return true;
//}
//
//void init(void) {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glEnable(GL_DEPTH_TEST);
//    // The following two lines enable semi transparent
//    glEnable(GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    
//    int width, height;
//    bool hasAlpha;
//    char filename[] = "logo.png";
//    bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
//    if (!success) {
//        std::cout << "Unable to load png file" << std::endl;
//        return;
//    }
//    std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//    glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
//                 height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
//                 textureImage);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glEnable(GL_TEXTURE_2D);
//    glShadeModel(GL_FLAT);
//}
//
//void display(void) {
//    glLoadIdentity();
//    glTranslatef(0.0, 0.0, -3.6);
//    glRotatef(rotateX, 0,1,0);
//    glRotatef(rotateY, 1,0,0);
//    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0);
//    glVertex3f(-2.0, -1.0, 0.0);
//    glTexCoord2f(0.0, 1.0);
//    glVertex3f(-2.0, 1.0, 0.0);
//    glTexCoord2f(1.0, 1.0);
//    glVertex3f(0.0, 1.0, 0.0);
//    glTexCoord2f(1.0, 0.0);
//    glVertex3f(0.0, -1.0, 0.0);
//    
//    glEnd();
//    glutSwapBuffers();
//}
//
//void myReshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 30.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void mousePassive(int x, int y){
//    mouseX = x;
//    mouseY = y;
//}
//
//void mouseMotion(int x, int y){
//    const float SPEED = 2;
//    
//    rotateX += (mouseX-x)/SPEED;
//    rotateY += (mouseY-y)/SPEED;
//    mousePassive(x, y);
//    glutPostRedisplay();
//}
//
//int
//main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
//    glutCreateWindow("PNG texture");
//    glutMotionFunc(mouseMotion);
//    glutPassiveMotionFunc(mousePassive);
//    init();
//    glutReshapeFunc(myReshape);
//    glutDisplayFunc(display);
//    std::cout << "Use mouse drag to rotate." << std::endl;
//    glutMainLoop();
//    return 0;
//}