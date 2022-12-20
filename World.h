#pragma once
#include <vector>
#include "SimplexNoise.hpp"
#include "TileAttrib.h"
#include "Tile.h"

class World
{
public:
	World(int seed, int id, bool isDef, int portalLocT, int portalLocB, TileAttrib&);

	int getTile(int x, int y, int z);
	void setTile(int x, int y, int z, int id);
	int getWidth();
	int getLength();
	int getHeight();
	int getID();
	void genPortal();
private:
	void init();
	void decorate(TileAttrib&);
	void genDefault(TileAttrib&);
	void genIslands(TileAttrib&);
	void genHills(TileAttrib&);
	void genRand(TileAttrib&);

	std::vector<std::vector<std::vector<Tile>>> tiles;
	int width, length, height, id, seed, portalLocT, portalLocB;
	SimplexNoise noise;
};

