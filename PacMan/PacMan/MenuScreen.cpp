#include "MenuScreen.h"
#include "GameScreen.h"
#include <SOIL.h>

MenuScreen::MenuScreen(ScreenManager* manager, GLFWwindow* window)
	:IScreen(manager, window), start(-0.8,0.0,0.5,0.3), exit(-0.8,-0.4,0.5,0.3)
{
	mActive = true;
	Input* i = Input::GetInstance();

	//sstart.LoadImange("bilder/play.bmp",Sprite::BMP_24BIT_TEXTURE);
	//sstart.GenerateTexture();
	sstart.mTextureId = SOIL_load_OGL_texture("bilder/play.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
	sstart.BindTexture();

	//sexit.LoadImange("bilder/exit.bmp",Sprite::BMP_24BIT_TEXTURE);
	//sexit.GenerateTexture();
	sexit.mTextureId = SOIL_load_OGL_texture("bilder/exit.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
	sexit.BindTexture();

	//sbackgound.LoadImange("bilder/example menu.bmp",Sprite::BMP_24BIT_TEXTURE);
	//sbackgound.GenerateTexture();
	sbackgound.mTextureId = SOIL_load_OGL_texture("bilder/example menu.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
	sbackgound.BindTexture();
	sbackgound.Set(-1, -1, 2, 2);

	start.SetSprite(&sstart);
	exit.SetSprite(&sexit);

	start.SetClickCallback([&](GLFWwindow* window, int button, int pressed, double x, double y)->void
	{
		if(mActive && start.Intersect(x,y))
		{
			GameScreen* game = new GameScreen(mManager, mWindow);
			mManager->AddScreen(game);
			mManager->SetFocus(game);
			mActive = false;
		}
	});

	exit.SetClickCallback([&](GLFWwindow* window, int button, int pressed, double x, double y)->void
	{
		if(mActive && exit.Intersect(x,y))
			glfwSetWindowShouldClose(mWindow, GL_TRUE);
	});

	i->Register(start);
	i->Register(exit);
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Draw()
{
	if(mActive)
	{
		sbackgound.Draw();
		start.Draw();
		exit.Draw();
	}
}

void MenuScreen::Update()
{
	if(mActive)
	{

	}
}