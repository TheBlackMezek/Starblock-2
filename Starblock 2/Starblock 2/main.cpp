

#include "MathLib\Vec2.h"
#include "sfwdraw.h"









int main()
{
	sfw::initContext(800, 600, "MathTest");

	sfw::setBackgroundColor(BLACK);

	vec2 pos = { 100, 100 };

	while (sfw::stepContext())
	{
		sfw::drawCircle(pos.x, pos.y, 20);
	}

	return 0;
}

