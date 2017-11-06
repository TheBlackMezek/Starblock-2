#pragma once

#include "shapes.h"

struct Collision
{
	float penetrationDepth;
	int handedness;
	vec2 axis;
};

Collision intersect1D(float Amin, float Amax, float Bmin, float Bmax);

Collision intersectAABB(const AABB& A, const AABB& B);

Collision intersectCircle(const circle& A, const circle& B);

Collision intersectCircleAABB(const circle& A, const AABB& B);

