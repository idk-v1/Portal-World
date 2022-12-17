#pragma once
#include <vector>
#include "SimplexNoise.hpp"
#include "Tile.h"

class World
{
public:
	World(int seed, int id, bool isDef, int portalLocT, int portalLocB);

	int getTile(int x, int y, int z);
	void setTile(int x, int y, int z, int id);
	int getWidth();
	int getLength();
	int getHeight();
	int getID();
	void genPortal();
private:
	void genDefault();
	void genIslands();
	void genHills();
	void genRand();

	std::vector<std::vector<std::vector<Tile>>> tiles;
	int width, length, height, id, seed, portalLocT, portalLocB;
	SimplexNoise noise;
};

