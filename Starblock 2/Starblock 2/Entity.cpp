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
