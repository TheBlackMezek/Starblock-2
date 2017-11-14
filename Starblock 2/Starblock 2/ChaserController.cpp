#include "ChaserController.h"

#include "World.h"
#include "Entity.h"


ChaserController::ChaserController()
{
}


ChaserController::~ChaserController()
{
}

void ChaserController::update(World& world, Entity& entity, Entity& player)
{
	vec2 toPlayer = player.trans.pos - entity.trans.pos;
	normalize(toPlayer);
	entity.body.force += toPlayer * 100;
}
