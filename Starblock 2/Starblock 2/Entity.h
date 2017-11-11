#pragma once


#include "MathLib\Collider.h"
#include "MathLib\Rigidbody.h"
#include "MathLib\Transform.h"

#include "Sprite.h"



class Entity
{
public:
	Entity();
	~Entity();

	Collider collider;
	Rigidbody body;
	Transform trans;
	Sprite sprite;

	bool onGround;

	void update(float dt);
	void draw();
};

