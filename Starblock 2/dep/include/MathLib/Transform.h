#pragma once


#include "Vec2.h"
#include "Mat3.h"


class Transform
{
public:
	Transform();
	~Transform();

	vec2 pos;
	vec2 disfigure;
	float angleRad;
	Transform* parent;

	Mat3 getLocalTransform() const;
	Mat3 getGlobalTransform() const;
	vec2 getForwardFacing() const;
	vec2 getUpFacing() const;
};

