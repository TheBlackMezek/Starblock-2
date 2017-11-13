#include "Entity.h"



Entity::Entity()
{
	onGround = false;
	active = true;
}


Entity::~Entity()
{
}


void Entity::update(float dt)
{
	body.integrate(trans, dt);
}

void Entity::draw()
{
	sprite.draw(trans);
}

vec2 Entity::getCenter()
{
	return vec2{ trans.pos.x + (collider.box.max.x - collider.box.min.x) / 2,
				 trans.pos.y + (collider.box.max.y - collider.box.min.y) / 2 };
}
