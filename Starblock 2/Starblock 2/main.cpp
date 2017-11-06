
#include <string>

#include "MathLib\Vec2.h"
#include "MathLib\shapes.h"
#include "sfwdraw.h"

#include "Textures.h"
#include "DrawShapes.h"








int main()
{
	sfw::initContext(800, 600, "MathTest");

	sfw::setBackgroundColor(BLACK);

	Textures::init();

	vec2 pos = { 100, 100 };
	AABB box;
	box.min = { 100, 100 };
	box.max = { 200, 300 };
	std::string line = "Rise and shine, Mr. Freeman.";


	while (sfw::stepContext())
	{
		sfw::drawCircle(pos.x, pos.y, 20);
		drawBox(box);
		writeString(line.c_str(), line.length(), 200, 300, 10);
		//writeString(line.c_str(), line.length(), 200, 300, 1);
		//writeString(line.c_str(), line.length(), 200, 300, 100);
	}

	return 0;
}

