#pragma once

#include "Vec2.h"

union vec3
{
	// access as vec2
	struct { vec2 xy; float z; };
	//access by array
	float v[3];	
	//access by individual component
	struct { float x, y, z; };
	

	float& operator[](const size_t idx);
	const float& operator[](const size_t idx) const;
};

vec3 operator+(const vec3 &lhs, const vec3 &rhs);
vec3 operator-(const vec3 &lhs, const vec3 &rhs);
vec3 operator*(const vec3 &lhs, const float &rhs);
vec3 operator*(const float &lhs, const vec3 &rhs);
vec3 operator/(const vec3 &lhs, const float &rhs);
vec3 operator-(const vec3 &rhs);

vec3& operator+=(vec3& lhs, const vec3& rhs);
vec3& operator-=(vec3& lhs, const vec3& rhs);
vec3& operator*=(vec3& lhs, const float& rhs);
vec3& operator/=(vec3& lhs, const float& rhs);

bool operator==(const vec3 &lhs, const vec3 &rhs);
bool operator!=(const vec3 &lhs, const vec3 &rhs);




float magnitude(vec3 vec);
vec3 normal(vec3 vec);
vec3& normalize(vec3& vec);
float dot(vec3 v1, vec3 v2);
float distance(vec3 v1, vec3 v2);
vec3 min(vec3 v1, vec3 v2);
vec3 max(vec3 v1, vec3 v2);
vec3 cross(vec3 v1, vec3 v2);
