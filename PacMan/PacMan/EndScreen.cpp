#include "EndScreen.h"
#include <SOIL.h>


EndScreen::EndScreen(ScreenManager* manager, GLFWwindow* window)
	:IScreen(manager, window)
{
	mEndSprite.mTextureId = SOIL_load_OGL_texture("bilder/game_over.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
	mEndSprite.BindTexture();
	mEndSprite.Set(-1, -1, 2, 2);
}


EndScreen::~EndScreen(void)
{
}


void EndScreen::Draw()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	mEndSprite.Draw();
}

void EndScreen::Update()
{

}