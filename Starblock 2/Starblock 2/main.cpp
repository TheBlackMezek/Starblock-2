
#include <string>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "MathLib\Vec2.h"
#include "MathLib\shapes.h"
#include "sfwdraw.h"

#include "Textures.h"
#include "DrawShapes.h"
#include "World.h"
#include "Entity.h"
#include "ChaserController.h"
#include "TextField.h"



float vectorToRadians(vec2 a);
std::string getTimeString(int seconds);
void endGame();
void onNameEntered();
void loadHighScores();

int screen = 1;
std::string highScores = "";



std::vector<Entity> enemies;
std::vector<Entity> fallingEnemies;
std::vector<ChaserController> enemyControllers;
std::vector<Entity> rocks;
std::vector<Entity> fallingRocks;

World world;

Entity entity;

bool firstStep = true;
vec2 mouseTile = { -1,-1 };
vec2 mousePos;
const float maxBlockDist = 150;
const int bulletMax = 100;
const float bulletSpeed = 1000;
Entity bullets[bulletMax];

float spawnCooldownMax = 1;
float spawnCooldown = spawnCooldownMax;
float rockCooldownMax = 1;
float rockCooldown = rockCooldownMax;
float gunCooldownMax = 0.1f;
float gunCooldown = gunCooldownMax;

float timeSurvived = 0;

const int highScoreCount = 10;

bool shouldContinue = true;

TextField tfield;



int main()
{
	srand(time(NULL));

	sfw::initContext(800, 600, "Starblock 2");

	//sfw::setBackgroundColor(GRE);

	Textures::init();

	world.gen();

	loadHighScores();

	tfield.callback = onNameEntered;

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


	for (int i = 0; i < bulletMax; ++i)
	{
		bullets[i].active = false;
		bullets[i].body.drag = 0;
		bullets[i].collider.box = { { 0, 0 },{ 6, 6 } };
	}




	
	while (sfw::stepContext() && shouldContinue)
	{
		float dt = sfw::getDeltaTime();
		if (firstStep)
		{
			dt = 0;
			firstStep = false;
		}

		shouldContinue = !sfw::getKey(256);

		mousePos = { sfw::getMouseX(), sfw::getMouseY() };

		sfw::drawTexture(Textures::background, 400, 300, 800, 600);

		if (screen == 0)
		{
			spawnCooldown = (spawnCooldown - dt) * (0 < spawnCooldown - dt);
			rockCooldown = (rockCooldown - dt) * (0 < rockCooldown - dt);
			gunCooldown = (gunCooldown - dt) * (0 < gunCooldown - dt);
			timeSurvived += dt;

			float mouseDist = distance(mousePos, entity.getCenter());
			mouseTile = { (float)((int)mousePos.x / (int)world.tileSize),
							(float)((int)mousePos.y / (int)world.tileSize) };

			//if (!sfw::getKey(340) && sfw::getMouseButton(0) && mouseDist <= maxBlockDist)
			//{
				//world.setTile(mouseTile.x, mouseTile.y, 1);
			//}
			//else if (!sfw::getKey(340) && sfw::getMouseButton(1) && mouseDist <= maxBlockDist)
			if (sfw::getMouseButton(1) && mouseTile.y > 0 && mouseDist <= maxBlockDist)
			{
				world.setTile(mouseTile.x, mouseTile.y, 0);
			}
			//else if (sfw::getKey(340) && sfw::getMouseButton(0))
			if (sfw::getMouseButton(0) && gunCooldown == 0)
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

						gunCooldown = gunCooldownMax;
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
				chaser.sprite.texId = Textures::enemy;
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
			entity.body.impulse.y += (sfw::getKey('W') || sfw::getKey(32)) * 900 * entity.onGround;

			entity.update(dt);
			world.collide(entity);

			if (entity.trans.pos.y < 0)
			{
				endGame();
			}

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

					for (int n = enemies.size() - 1; n >= 0; --n)
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
					endGame();
					break;
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
					endGame();
					break;
				}

				if (world.collide(rocks[i]))
				{
					world.setTile((float)((int)rocks[i].trans.pos.x / (int)world.tileSize),
						(float)((int)rocks[i].trans.pos.y / (int)world.tileSize),
						1);
					rocks.erase(rocks.begin() + i);
				}
			}


			//std::string surviveString = getTimeString((int)timeSurvived);

			world.draw();

			std::string surviveString = std::to_string((int)timeSurvived);
			writeString(surviveString.c_str(), surviveString.size(), 10, 550, 30);

			if (mouseDist <= maxBlockDist && mouseTile.y > 0 && world.getTile(mouseTile.x, mouseTile.y))
			{
				drawBox({ mouseTile * world.tileSize,
						{(mouseTile.x * world.tileSize) + world.tileSize, (mouseTile.y * world.tileSize) + world.tileSize }
				});
			}

			for (int i = 0; i < bulletMax; ++i)
			{
				if (bullets[i].active)
				{
					//sfw::drawCircle(bullets[i].trans.pos.x, bullets[i].trans.pos.y, 3);
					float rad = bullets[i].trans.angleRad;
					bullets[i].trans.angleRad = 0;
					drawTexture(Textures::bullet,
						bullets[i].collider.getGlobalBox(bullets[i].trans));
					bullets[i].trans.angleRad = rad;
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
		}
		else if(screen == 1)
		{
			screen = !sfw::getKey(32);

			std::string printStr = "STARBLOCK 2";
			float center = 400 - (printStr.size() * 30) / 2;
			writeString(printStr.c_str(), printStr.size(), center, 580, 30);

			printStr = "HIGH SCORES";
			writeString(printStr.c_str(), printStr.size(), 50, 520, 20);

			printStr = "Press SPACE to play\n"
				"CONTROLS: A & D to move\nW or SPACE to jump\nLMB to shoot\n"
				"RMB to destroy blocks\nESC to exit";
			writeString(printStr.c_str(), printStr.size(), 20, 150, 23, 3);

			writeString(highScores.c_str(), highScores.size(), 50, 480, 30);
		}
		else if (screen == 2)
		{
			tfield.update();
			std::string nameStr = tfield.getString();
			float center = 400 - (nameStr.size() * 30) / 2;
			writeString(nameStr.c_str(), nameStr.size(), center, 400, 30);

			std::string endStr = "GAME OVER";
			center = 400 - (endStr.size() * 30) / 2;
			writeString(endStr.c_str(), endStr.size(), center, 580, 30);

			std::string helpStr = "SCORE:" + std::to_string((int)timeSurvived);
			center = 400 - (helpStr.size() * 20) / 2;
			writeString(helpStr.c_str(), helpStr.size(), center, 480, 25);

			helpStr = "Type your name and press ENTER";
			center = 400 - (helpStr.size() * 20) / 2;
			writeString(helpStr.c_str(), helpStr.size(), center, 450, 20);
		}

		sfw::drawCircle(mousePos.x, mousePos.y, 3, 12U, YELLOW);
	}

	return 0;
}

float vectorToRadians(vec2 m)
{
	normalize(m);
	return atan2(-m.y, m.x);
}

std::string getTimeString(int seconds)
{
	std::string ret = "";
	int minutes = 0;
	int hours = 0;
	int days = 0;

	while (seconds >= 60)
	{
		seconds -= 60;
		++minutes;
	}
	while (minutes >= 60)
	{
		minutes -= 60;
		++hours;
	}
	while (hours >= 24)
	{
		hours -= 24;
		++days;
	}

	if (days > 0)
	{
		ret.append(std::to_string(days));
		ret.append(":");
	}
	if (days > 0 || hours > 0)
	{
		ret.append(std::to_string(hours));
		ret.append(":");
	}
	if (days > 0 || hours > 0 || minutes > 0)
	{
		ret.append(std::to_string(minutes));
		ret.append(":");
	}
	ret.append(std::to_string(seconds));

	return ret;
}

void endGame()
{
	if (screen != 2)
	{
		screen = 2;

		enemies.clear();
		enemyControllers.clear();
		fallingEnemies.clear();
		rocks.clear();
		fallingRocks.clear();
		world.gen();
		entity.trans.pos = { 100, 200 };
		for (int i = 0; i < bulletMax; ++i)
		{
			bullets[i].active = false;
		}
		rockCooldown = rockCooldownMax;
		spawnCooldown = spawnCooldownMax;
		
		tfield.reset();
	}
}

void onNameEntered()
{
	screen = 1;

	int seconds = (int)timeSurvived;
	timeSurvived = 0;

	std::ofstream file;
	file.open("highscore.txt", std::fstream::app);

	file << std::to_string(seconds) << " " << tfield.getString() << '\n';

	file.close();


	loadHighScores();
}

void loadHighScores()
{
	std::ifstream ifile;
	ifile.open("highscore.txt");

	int top[highScoreCount];
	for (int i = 0; i < highScoreCount; ++i)
	{
		top[i] = 0;
	}
	std::string topNames[highScoreCount];
	for (int i = 0; i < highScoreCount; ++i)
	{
		topNames[i] = "";
	}

	std::string line;

	while (std::getline(ifile, line))
	{
		int score = std::stoi(line.substr(0, line.find(' ')));
		std::string name = line.substr(line.find(' '), line.npos);
		for (int i = highScoreCount - 1; i >= 0; --i)
		{
			if (top[i] <= score)
			{
				for (int n = 0; n < i; ++n)
				{
					top[n] = top[n + 1];
					topNames[n] = topNames[n + 1];
				}
				top[i] = score;
				topNames[i] = name;
				break;
			}
		}
	}

	highScores = "";
	for (int i = highScoreCount - 1; i >= 0; --i)
	{
		std::string scorestr = std::to_string(top[i]);
		std::string initspaces = "";
		for (int n = 0; n < 10 - scorestr.size(); ++n)
		{
			initspaces = initspaces + ' ';
		}
		highScores = highScores + initspaces + std::to_string(top[i]) + topNames[i] + '\n';
	}

	ifile.close();
}
