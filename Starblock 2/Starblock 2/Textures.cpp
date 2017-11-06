#include "Textures.h"

#include "sfwdraw.h"


int Textures::stringBitmap;



Textures::Textures()
{
}


Textures::~Textures()
{
}

void Textures::init()
{
	stringBitmap = sfw::loadTextureMap("Images\16x16fontmap.gif", 16, 16);
}
