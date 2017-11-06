#pragma once



union vec2
{
	//access by array
	float v[2];

	//access by individual component
	struct { float x, y; };

	float& operator[]( const size_t idx );
	const float& operator[](const size_t idx) const;
};

vec2 operator+(const vec2 &lhs, const vec2 &rhs);
vec2 operator-(const vec2 &lhs, const vec2 &rhs);
vec2 operator*(const vec2 &lhs, const float &rhs);
vec2 operator*(const float &lhs, const vec2 &rhs);
vec2 operator/(const vec2 &lhs, const float &rhs);
vec2 operator-(const vec2 &rhs);

vec2& operator+=(vec2& lhs, const vec2& rhs);
vec2& operator-=(vec2& lhs, const vec2& rhs);
vec2& operator*=(vec2& lhs, const float& rhs);
vec2& operator/=(vec2& lhs, const float& rhs);

bool operator==(const vec2 &lhs, const vec2 &rhs);
bool operator!=(const vec2 &lhs, const vec2 &rhs);




float magnitude(vec2 vec);
vec2 normal(vec2 vec);
vec2& normalize(vec2& vec);
float dot(vec2 v1, vec2 v2);
float angle(vec2 v1, vec2 v2);
bool isAngleClockwise(vec2 v1, vec2 v2);
float distance(vec2 v1, vec2 v2);
vec2 perpendicular(vec2 vec, bool clockwise);
vec2 lerp(vec2 s, vec2 e, float a);
vec2 min(vec2 v1, vec2 v2);
vec2 max(vec2 v1, vec2 v2);
