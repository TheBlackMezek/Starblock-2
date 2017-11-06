#include "DrawShapes.h"

#include "sfwdraw.h"

#include "Textures.h"




void drawCircle(const circle& c)
{
	sfw::drawCircle(c.pos.x, c.pos.y, c.radius);
}

void drawBox(const AABB& box)
{
	sfw::drawLine(box.min.x, box.min.y, box.max.x, box.min.y);
	sfw::drawLine(box.min.x, box.max.y, box.max.x, box.max.y);
	sfw::drawLine(box.min.x, box.min.y, box.min.x, box.max.y);
	sfw::drawLine(box.max.x, box.min.y, box.max.x, box.max.y);
}

void writeString(const char* s, size_t slen, int x, int y, float size, int lines)
{
	sfw::drawString(Textures::stringBitmap, s, x, y, size, size);
}
