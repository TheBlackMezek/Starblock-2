#include "Controller.h"

#include "Entity.h"
#include "World.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::update(World& world, Entity& entity, Entity& player)
{
	entity.body.force.x += 100;
}
