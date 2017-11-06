#pragma once


#include "MathLib\Vec2.h"
#include "MathLib\Transform.h"
#include "MathLib\Mat3.h"



class Sprite
{
public:
	Sprite();
	~Sprite();

	int texId;
	vec2 dim;
	vec2 offset;

	void draw(const Transform& t, const Mat3& cam = mat3identity());
};

