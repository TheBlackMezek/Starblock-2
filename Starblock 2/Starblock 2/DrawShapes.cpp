#include "DrawShapes.h"

#include "sfwdraw.h"




void drawCircle(const circle& c)
{
	sfw::drawCircle(c.pos.x, c.pos.y, c.radius);
}
