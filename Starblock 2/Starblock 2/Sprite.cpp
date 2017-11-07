#include "Sprite.h"

#include "sfwdraw.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}


void Sprite::draw(const Transform& t, const Mat3& cam)
{
	Mat3 M = cam * t.getGlobalTransform() * translation(offset) * scaleMat(dim);

	M[6] += dim.x / 2;
	M[7] += dim.y / 2;

	sfw::drawTextureMatrix3(texId, 0, WHITE, M.m);
}
