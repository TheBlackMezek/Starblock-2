#include "Sprite.h"

#include "sfwdraw.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}


void Sprite::draw(const Transform& t, const Mat3& cam = mat3identity())
{
	Mat3 M = cam * t.getGlobalTransform() * translation(offset) * scaleMat(dim);

	sfw::drawTextureMatrix3(texId, 0, WHITE, M.m);
}
