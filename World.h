#pragma once
#include <vector>
#include "SimplexNoise.hpp"
#include "Tile.h"

class World
{
public:
	World(int, int, int);

	char getTile(int, int, int);
	void setTile(int, int, int, int);
	attrib getTileAttrib(int, int, int);
	int getWidth();
	int getLength();
	int getHeight();
private:
	std::vector<std::vector<std::vector<Tile>>> tiles;
	int width, length, height;
	SimplexNoise noise;
};

