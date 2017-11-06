
#include <string>
#include <time.h>

#include "MathLib\Vec2.h"
#include "MathLib\shapes.h"
#include "sfwdraw.h"

#include "Textures.h"
#include "DrawShapes.h"
#include "World.h"








int main()
{
	srand(time(NULL));

	sfw::initContext(800, 600, "MathTest");

	sfw::setBackgroundColor(BLACK);

	Textures::init();

	World world;
	world.gen();


	while (sfw::stepContext())
	{
		world.draw();
	}

	return 0;
}

