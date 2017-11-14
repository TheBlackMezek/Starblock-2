
#include <string>
#include <time.h>
#include <iostream>
#include <vector>

#include "MathLib\Vec2.h"
#include "MathLib\shapes.h"
#include "sfwdraw.h"

#include "Textures.h"
#include "DrawShapes.h"
#include "World.h"
#include "Entity.h"
#include "ChaserController.h"



float vectorToRadians(vec2 a);




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
	Entity fallingEntity;
	fallingEntity.trans.pos = { 100, 200 };
	fallingEntity.body.drag = 10;
	fallingEntity.collider.box = { { 0, 0 },{ 30, 30 } };
	fallingEntity.sprite.texId = Textures::moonDust;
	fallingEntity.sprite.dim = { 30, 30 };


	std::vector<Entity> enemies;
	std::vector<Entity> fallingEnemies;
	std::vector<ChaserController> enemyControllers;
	std::vector<Entity> rocks;
	std::vector<Entity> fallingRocks;

	



	bool firstStep = true;
	vec2 mouseTile = { -1,-1 };
	vec2 mousePos;
	const float maxBlockDist = 150;
	const int bulletMax = 100;
	const float bulletSpeed = 1000;
	Entity bullets[bulletMax];
	for (int i = 0; i < bulletMax; ++i)
	{
		bullets[i].active = false;
		bullets[i].body.drag = 0;
		bullets[i].collider.box = { {0, 0},{6, 6} };
	}

	float spawnCooldownMax = 1;
	float spawnCooldown = spawnCooldownMax;
	float rockCooldownMax = 1;
	float rockCooldown = rockCooldownMax;

	bool shouldRun = true;


	
	while (sfw::stepContext() && shouldRun)
	{
		float dt = sfw::getDeltaTime();
		if (firstStep)
		{
			dt = 0;
			firstStep = false;
		}

		spawnCooldown = (spawnCooldown - dt) * (0 < spawnCooldown - dt);
		rockCooldown = (rockCooldown - dt) * (0 < rockCooldown - dt);

		mousePos = { sfw::getMouseX(), sfw::getMouseY() };
		float mouseDist = distance(mousePos, entity.getCenter());
		mouseTile = {	(float)((int)mousePos.x / (int)world.tileSize),
						(float)((int)mousePos.y / (int)world.tileSize) };

		//if (!sfw::getKey(340) && sfw::getMouseButton(0) && mouseDist <= maxBlockDist)
		//{
			//world.setTile(mouseTile.x, mouseTile.y, 1);
		//}
		//else if (!sfw::getKey(340) && sfw::getMouseButton(1) && mouseDist <= maxBlockDist)
		if(sfw::getMouseButton(1) && mouseDist <= maxBlockDist)
		{
			world.setTile(mouseTile.x, mouseTile.y, 0);
		}
		//else if (sfw::getKey(340) && sfw::getMouseButton(0))
		else if (sfw::getMouseButton(0))
		{
			for (int i = 0; i < bulletMax; ++i)
			{
				if (!bullets[i].active)
				{
					bullets[i].active = true;
					bullets[i].trans.pos = entity.getCenter();
					bullets[i].body.velocity = { 0,0 };
					bullets[i].body.acceleration = { 0,0 };
					bullets[i].body.force = { 0,0 };

					vec2 playerToMouse = mousePos - entity.getCenter();
					bullets[i].trans.angleRad = vectorToRadians(playerToMouse);
					bullets[i].body.impulse = bullets[i].trans.getForwardFacing() * bulletSpeed;

					//bullets[i].body.impulse = { bulletSpeed,0 };
					//bullets[i].trans. //how to get rotation?
					break;
				}
			}
		}

		if (spawnCooldown == 0)
		{
			Entity chaser;
			chaser.trans.pos = { (float)(rand() % 800), 600 };
			chaser.collider.box = { { 0, 0 },{ 10, 10 } };
			chaser.sprite.texId = Textures::moonDust;
			chaser.sprite.dim = { 10, 10 };
			enemies.push_back(chaser);
			fallingEnemies.push_back(chaser);
			ChaserController cc;
			enemyControllers.push_back(cc);

			spawnCooldown = spawnCooldownMax;
		}

		if (rockCooldown == 0)
		{
			Entity rock;
			rock.trans.pos = { (float)(rand() % world.mapWidth) * world.tileSize, 600 };
			rock.collider.box = { { 0, 0 },{ world.tileSize, world.tileSize } };
			rock.sprite.texId = Textures::moonRock;
			rock.sprite.dim = { world.tileSize, world.tileSize };
			rocks.push_back(rock);
			fallingRocks.push_back(rock);

			rockCooldown = rockCooldownMax;
		}





		//entity.body.force.y = -50;
		//entity.body.force.y -= 1000;
		fallingEntity.trans.pos = entity.trans.pos;
		fallingEntity.body.force.y -= 1000;
		fallingEntity.update(dt);
		
		bool fallHit = world.collide(fallingEntity);
		entity.body.force.y -= 1000 * !fallHit;
		entity.onGround = fallHit;

		entity.body.force.x += sfw::getKey('A') * -1000;
		entity.body.force.x += sfw::getKey('D') * 1000;
		entity.body.impulse.y += sfw::getKey('W') * 900 * entity.onGround;

		entity.update(dt);
		world.collide(entity);

		for (int i = 0; i < bulletMax; ++i)
		{
			if (bullets[i].active)
			{
				bullets[i].update(dt);
				if (bullets[i].trans.pos.x < 0 || bullets[i].trans.pos.x > 800 ||
					bullets[i].trans.pos.y < 0 || bullets[i].trans.pos.y > 600)
				{
					bullets[i].active = false;
					continue;
				}
				bullets[i].active = !world.collide(bullets[i]);

				for (int n = enemies.size()-1; n >= 0; --n)
				{
					Collision col = intersectAABB(enemies[n].collider.getGlobalBox(enemies[n].trans),
						bullets[i].collider.getGlobalBox(bullets[i].trans));
					if (col.penetrationDepth > 0)
					{
						enemies.erase(enemies.begin() + n);
						bullets[i].active = false;
						break;
					}
				}
			}
		}

		for (int i = 0; i < enemies.size(); ++i)
		{
			fallingEnemies[i].trans.pos = enemies[i].trans.pos;
			fallingEnemies[i].body.force.y -= 100;
			fallingEnemies[i].update(dt);
			fallHit = world.collide(fallingEnemies[i]);

			enemies[i].onGround = fallHit;
			enemies[i].body.force.y -= 100 * !fallHit;
			enemyControllers[i].update(world, enemies[i], entity);
			enemies[i].update(dt);
			world.collide(enemies[i]);

			Collision col = intersectAABB(enemies[i].collider.getGlobalBox(enemies[i].trans),
				entity.collider.getGlobalBox(entity.trans));
			if (col.penetrationDepth > 0)
			{
				shouldRun = false;
			}
		}

		for (int i = rocks.size() - 1; i >= 0; --i)
		{
			fallingRocks[i].trans.pos = rocks[i].trans.pos;
			fallingRocks[i].body.force.y -= 100;
			fallingRocks[i].update(dt);
			fallHit = world.collide(fallingRocks[i]);

			rocks[i].onGround = fallHit;
			rocks[i].body.force.y -= 100 * !fallHit;
			rocks[i].update(dt);

			Collision col = intersectAABB(rocks[i].collider.getGlobalBox(rocks[i].trans),
				entity.collider.getGlobalBox(entity.trans));
			if (col.penetrationDepth > 0)
			{
				shouldRun = false;
			}

			if (world.collide(rocks[i]))
			{
				world.setTile(	(float)((int)rocks[i].trans.pos.x / (int)world.tileSize),
								(float)((int)rocks[i].trans.pos.y / (int)world.tileSize),
								1);
				rocks.erase(rocks.begin() + i);
			}
		}

		

		sfw::drawCircle(mousePos.x, mousePos.y, 3);

		if (mouseDist <= maxBlockDist)
		{
			drawBox({ mouseTile * world.tileSize,
					{(mouseTile.x * world.tileSize) + world.tileSize, (mouseTile.y * world.tileSize) + world.tileSize }
			});
		}

		for (int i = 0; i < bulletMax; ++i)
		{
			if (bullets[i].active)
			{
				sfw::drawCircle(bullets[i].trans.pos.x, bullets[i].trans.pos.y, 3);
			}
		}

		for (int i = 0; i < enemies.size(); ++i)
		{
			enemies[i].draw();
		}

		for (int i = 0; i < rocks.size(); ++i)
		{
			rocks[i].draw();
		}

		entity.draw();
		world.draw();
		sfw::drawTexture(Textures::background, 400, 300, 800, 600);
	}

	return 0;
}

float vectorToRadians(vec2 m)
{
	normalize(m);
	return atan2(-m.y, m.x);
}
