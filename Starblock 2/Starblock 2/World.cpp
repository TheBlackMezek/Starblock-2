#include "World.h"

#include <stdlib.h>
#include <iostream>

#include "sfwdraw.h"
#include "MathLib\Collision.h"
#include "MathLib\Collider.h"

#include "DrawShapes.h"
#include "Textures.h"
#include "Entity.h"



World::World()
	: tileSize(20), mapWidth(40), mapHeight(25)
{
	tiles.resize(mapWidth * mapHeight);

	for (int i = 0; i < mapWidth * mapHeight; ++i)
	{
		tiles[i] = 0;
	}
}


World::~World()
{
}




void World::gen()
{
	for (int i = 0; i < mapWidth * mapHeight; ++i)
	{
		//tiles[i] = rand() % 2;
		if (i < 5 * mapWidth)
		{
			tiles[i] = 1;
		}
		else
		{
			tiles[i] = 0;
		}
	}
}

void World::draw()
{
	for (float y = 0; y < mapHeight; ++y)
	{
		for (float x = 0; x < mapWidth; ++x)
		{
			if (tiles[x + y * mapWidth] != 0)
			{
				/*drawBox({ {x * tileSize, y * tileSize},
				{x * tileSize + tileSize, y * tileSize + tileSize} });*/
				sfw::drawTexture(Textures::moonRock,
					x * tileSize + tileSize/2, y * tileSize + tileSize/2,
					tileSize, tileSize);
			}
		}
	}
}




bool World::collide(Entity& e)
{
	bool ret = false;

	vec2 tileMin;
	tileMin.x = (int)(e.trans.pos.x / tileSize)+1;
	tileMin.y = (int)(e.trans.pos.y / tileSize)+1;
	vec2 tileMax;
	tileMax.x = (int)((e.trans.pos.x + e.collider.box.max.x - e.collider.box.min.x) / tileSize) + 1;
	tileMax.y = (int)((e.trans.pos.y + e.collider.box.max.y - e.collider.box.min.y) / tileSize) + 1;

	bool breaker = false;
	bool groundFlag = false;

	for (float y = tileMin.y; y <= tileMax.y && !breaker; ++y)
	{
		for (float x = tileMin.x; x <= tileMax.x && !breaker; ++x)
		{
			AABB tileBox;
			tileBox.max = vec2{x,y} * tileSize;
			tileBox.min = { x * tileSize - tileSize, y * tileSize - tileSize };
			if (getTile(x-1, y-1))
			{
				Collision col = intersectAABB(e.collider.getGlobalBox(e.trans), tileBox);
				if (col.penetrationDepth > 0)
				{
					ret = true;
					if (col.axis.y && col.handedness == 1)
					{
						groundFlag = true;
					}
					//std::cout << col.axis.x << "," << col.axis.y << "," << col.handedness << "," << col.penetrationDepth << std::endl;
					e.trans.pos += col.axis * col.handedness * (col.penetrationDepth/2);
					//breaker = true;
					//e.body.force += col.axis * col.handedness * (col.penetrationDepth);
					//e.body.force = { e.body.force.x * col.axis.x, e.body.force.y * col.axis.y };
					/*e.body.acceleration.x *= col.axis.y;
					e.body.acceleration.y *= col.axis.x;
					e.body.velocity.x *= col.axis.y;
					e.body.velocity.y *= col.axis.x;*/
				}
			}
		}
	}

	e.onGround = groundFlag;

	return ret;
}




int World::getTile(int x, int y)
{
	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
	{
		return tiles[x + y * mapWidth];
	}
	else
	{
		return 0;
	}
}
int World::getTile(int idx)
{
	if (idx >= 0 && idx < mapWidth * mapHeight)
	{
		return tiles[idx];
	}
	else
	{
		return 0;
	}
}
void World::setTile(int x, int y, int type)
{
	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
	{
		tiles[x + y * mapWidth] = type;
	}
}
void World::setTile(int idx, int type)
{
	if (idx >= 0 && idx < mapWidth * mapHeight)
	{
		tiles[idx] = type;
	}
}
