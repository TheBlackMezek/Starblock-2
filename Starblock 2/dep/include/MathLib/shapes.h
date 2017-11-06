#pragma once

#include "Vec2.h"
#include "Mat3.h"



struct circle
{
	vec2 pos;
	float radius;
};

struct AABB
{
	vec2 min;
	vec2 max;
};



inline vec2 aabb_pos(const AABB &B) { return (B.max + B.min) / 2; }
inline vec2 aabb_dim(const AABB &B) { return (B.max - B.min) / 2; }

inline AABB aabb_pos_dim(const vec2 &pos, const vec2 &dim)
{
	return AABB {(pos-dim) / 2, (pos+dim) / 2};
}




circle operator*(const Mat3 &M, const circle &C);

AABB operator*(const Mat3& M, const AABB& B);


