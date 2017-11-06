#pragma once


#include <vector>



class World
{
public:
	World();
	~World();

	const int mapWidth;
	const int mapHeight;
	const float tileSize;


	void gen();
	void draw();

	int getTile(int x, int y);
	int getTile(int idx);
	void setTile(int x, int y, int type);
	void setTile(int idx, int type);

private:
	std::vector<int> tiles;
};

