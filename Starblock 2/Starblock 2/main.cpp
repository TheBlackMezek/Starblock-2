
#include <string>
#include <time.h>

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
	entity.trans.pos = { 100, 600 };
	entity.body.drag = 10;
	entity.body.force.y = 400;
	entity.collider.box = { {0, 0},{30, 30} };
	entity.sprite.texId = Textures::moonDust;
	entity.sprite.dim = { 30, 30 };


	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();

		//entity.body.force.y = -50;
		entity.body.force.y -= 500;

		entity.body.force.x += sfw::getKey('A') * -1000;
		entity.body.force.x += sfw::getKey('D') * 1000;
		entity.body.impulse.y += sfw::getKey('W') * 1000 * entity.onGround;

		entity.update(dt);
		world.collide(entity);

		entity.draw();
		world.draw();
		sfw::drawTexture(Textures::background, 400, 300, 800, 600);
	}

	return 0;
}

