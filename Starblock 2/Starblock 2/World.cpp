#include "World.h"

#include <stdlib.h>

#include "sfwdraw.h"

#include "DrawShapes.h"
#include "Textures.h"



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
		tiles[i] = rand() % 2;
		/*if (i < 5 * mapWidth)
		{
			tiles[i] = 1;
		}
		else
		{
			tiles[i] = 0;
		}*/
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
				sfw::drawTexture(Textures::moonDust,
					x * tileSize + tileSize/2, y * tileSize + tileSize/2,
					tileSize, tileSize);
			}
		}
	}
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
