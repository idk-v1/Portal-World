#include "World.h"
#include <iostream>


World::World(int width, int length, int height, int seed)
{
	int hgt;
	std::vector<std::vector<Tile>> vvt;
	std::vector<Tile> vt;
	Tile t;

	portalLoc = std::hash<int>{}(seed) % width;

	noise.setSeed(seed);

	this->width = width;
	this->length = length;
	this->height = height;

	for (int w = 0; w < width; w++)
	{
		tiles.push_back(vvt);
		for (int l = 0; l < length; l++)
		{
			tiles[w].push_back(vt);
			for (int h = 0; h < height; h++)
				tiles[w][l].push_back(t);
		}
	}

	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
		{
			hgt = std::floor(pow(noise.unsignedFBM(w * 0.025, l * 0.025, 2, 0.1, 0.15) * (height - 1.0), 3) / (height - 1.0) + 0.75) / (height - 1.0);
			for (int h = 0; h < hgt - 1; h++)
			{
				setTile(w, l, h, 2);
			}
			if (getTile(w, l, 0) == 0)
				setTile(w, l, 0, 1);
		}
	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
		{
			if (getTile(w, l - 1, 0) == 1 || getTile(w + 1, l, 0) == 1 || getTile(w, l + 1, 0) == 1 || getTile(w - 1, l, 0) == 1)
				if (getTile(w, l, 0) == 2)
					setTile(w, l, 0, 3);
		}

	hgt = 1;
	for (int h = 0; h < height; h++)
		if (getTile(portalLoc, 0, h) != 0)
			hgt = h + 1;
	setTile(portalLoc, 0, hgt, 4);
	std::cout << "Portal is at: X: " << portalLoc << '\n';
}

attrib World::getTileAttrib(int x, int y, int z)
{
	if (x >= 0 && x < width && y >= 0 && y < length && z >= 0 && z < height)
		return tiles[x][y][z].getAttrib();
	return { -1, -1, -1, -1, false, true, false };
}

int World::getWidth()
{
	return width;
}

int World::getLength()
{
	return length;
}

int World::getHeight()
{
	return height;
}

int World::getTile(int x, int y, int z)
{
	if (x >= 0 && x < width && y >= 0 && y < length && z >= 0 && z < height)
		return tiles[x][y][z].getID();
	return -1;
}

void World::setTile(int x, int y, int z, int id)
{
	if (x >= 0 && x < width && y >= 0 && y < length && z >= 0 && z < height)
		tiles[x][y][z].setID(id);
}