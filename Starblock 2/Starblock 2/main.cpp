
#include <string>
#include <time.h>
#include <iostream>

#include "MathLib\Vec2.h"
#include "MathLib\shapes.h"
#include "sfwdraw.h"

#include "Textures.h"
#include "DrawShapes.h"
#include "World.h"
#include "Entity.h"








int main()
{
	srand(time(NULL));

	sfw::initContext(800, 600, "Starblock 2");

	sfw::setBackgroundColor(BLACK);

	Textures::init();

	World world;
	world.gen();

	Entity entity;
	entity.trans.pos = { 100, 200 };
	entity.body.drag = 10;
	//entity.body.force.y = 400;
	entity.collider.box = { {0, 0},{30, 30} };
	entity.sprite.texId = Textures::moonDust;
	entity.sprite.dim = { 30, 30 };

	bool firstStep = true;
	vec2 mouseTile = { -1,-1 };
	vec2 mousePos;
	const int bulletMax = 100;
	const float bulletSpeed = 10;
	Entity bullets[bulletMax];
	for (int i = 0; i < bulletMax; ++i)
	{
		bullets[i].active = false;
	}


	
	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();
		if (firstStep)
		{
			dt = 0;
			firstStep = false;
		}

		mousePos = { sfw::getMouseX(), sfw::getMouseY() };
		mouseTile = { (float)((int)mousePos.x / (int)world.tileSize), (float)((int)mousePos.y / (int)world.tileSize) };

		if (!sfw::getKey('Q') && sfw::getMouseButton(0))
		{
			world.setTile(mouseTile.x, mouseTile.y, 1);
		}
		else if (!sfw::getKey('Q') && sfw::getMouseButton(1))
		{
			world.setTile(mouseTile.x, mouseTile.y, 0);
		}
		else if (sfw::getKey('Q') && sfw::getMouseButton(0))
		{
			for (int i = 0; i < bulletMax; ++i)
			{
				if (!bullets[i].active)
				{
					bullets[i].active = true;
					bullets[i].trans.pos = entity.trans.pos;
					//bullets[i].trans. //how to get rotation?
					break;
				}
			}
		}

		//entity.body.force.y = -50;
		entity.body.force.y -= 1000;

		entity.body.force.x += sfw::getKey('A') * -1000;
		entity.body.force.x += sfw::getKey('D') * 1000;
		entity.body.impulse.y += sfw::getKey('W') * 900 * entity.onGround;

		entity.update(dt);
		world.collide(entity);
		
		drawBox({mouseTile * world.tileSize,
				{(mouseTile.x * world.tileSize) + world.tileSize, (mouseTile.y * world.tileSize) + world.tileSize }
		});

		entity.draw();
		world.draw();
		sfw::drawTexture(Textures::background, 400, 300, 800, 600);
	}

	return 0;
}

