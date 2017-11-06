

#include "MathLib\Vec2.h"
#include "MathLib\shapes.h"
#include "sfwdraw.h"

#include "DrawShapes.h"








int main()
{
	sfw::initContext(800, 600, "MathTest");

	sfw::setBackgroundColor(BLACK);

	vec2 pos = { 100, 100 };
	AABB box;
	box.min = { 100, 100 };
	box.max = { 129, 200 };


	while (sfw::stepContext())
	{
		sfw::drawCircle(pos.x, pos.y, 20);
		drawBox(box);
	}

	return 0;
}

