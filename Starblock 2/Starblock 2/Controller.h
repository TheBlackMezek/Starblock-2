#pragma once

class World;
class Entity;

class Controller
{
public:
	Controller();
	~Controller();

	virtual void update(World& world, Entity& entity, Entity& player);
};

