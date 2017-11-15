#include "Textures.h"

#include "sfwdraw.h"


int Textures::stringBitmap;
int Textures::moonDust;
int Textures::moonRock;
int Textures::background;
int Textures::enemy;



Textures::Textures()
{
}


Textures::~Textures()
{
}

void Textures::init()
{
	stringBitmap = sfw::loadTextureMap("Images\\16x16fontmap.png", 16, 16);
	moonDust = sfw::loadTextureMap("Images\\DustTexture.png");
	moonRock = sfw::loadTextureMap("Images\\RockTexture.png");
	background = sfw::loadTextureMap("Images\\StarBackground.png");
	enemy = sfw::loadTextureMap("Images\\EnemyTexture.png");
}
