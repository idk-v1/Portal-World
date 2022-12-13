#pragma once
#include <vector>
#include "SimplexNoise.hpp"

class World
{
public:
	World(int, int, int);
	
	char getTile(int, int, int);
	void setTile(int, int, int, int);
	int getWidth();
	int getLength();
	int getHeight();
private:
	std::vector<std::vector<std::vector<char>>> tiles;
	int width, length, height;
	SimplexNoise noise;
};

