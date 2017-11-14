#pragma once
#include "Controller.h"
class ChaserController : public Controller
{
public:
	ChaserController();
	~ChaserController();

	void update(World& world, Entity& entity, Entity& player);
};

