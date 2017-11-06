#include "World.h"



World::World()
	: tileSize(20), mapWidth(100), mapHeight(100)
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
