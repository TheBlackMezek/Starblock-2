#pragma once


#include "MathLib\Collider.h"
#include "MathLib\Rigidbody.h"
#include "MathLib\Transform.h"

#include "Sprite.h"
#include "Controller.h"



class Entity
{
public:
	Entity();
	~Entity();

	Collider collider;
	Rigidbody body;
	Transform trans;
	Sprite sprite;
	Controller controller;

	bool onGround;
	bool active;

	void update(float dt);
	void draw();
	vec2 getCenter();
};

