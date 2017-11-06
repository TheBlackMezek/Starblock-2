#include "Textures.h"

#include "sfwdraw.h"


int Textures::stringBitmap;
int Textures::moonDust;
int Textures::moonRock;
int Textures::background;



Textures::Textures()
{
}


Textures::~Textures()
{
}

void Textures::init()
{
	stringBitmap = sfw::loadTextureMap("Images\\16x16fontmap.gif", 16, 16);
	moonDust = sfw::loadTextureMap("Images\\DustTexture.png");
	moonRock = sfw::loadTextureMap("Images\\RockTexture.png");
	background = sfw::loadTextureMap("Images\\StarBackground.png");
}
