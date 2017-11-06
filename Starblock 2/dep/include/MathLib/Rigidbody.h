#pragma once



#include "Vec2.h"
#include "Transform.h"





class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();

	vec2 velocity;
	vec2 acceleration;
	vec2 force;
	vec2 impulse;
	float mass;
	float drag;

	float torque;
	float angularAcceleration;
	float angularVelocity;
	float angularDrag;


	void integrate(Transform& T, float dt);
};

