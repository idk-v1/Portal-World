#include "World.h"


World::World(int width, int length, int height)
{
	std::vector<std::vector<Tile>> vvt;
	std::vector<Tile> vt;
	Tile t;

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
			int hgt = std::floor(pow(noise.unsignedFBM(w * 0.05, l * 0.05, 5, 0.5, 0.15) * (height - 1.0), 3) / (height - 1.0) + 0.75) / (height - 1.0);
			for (int h = 0; h < hgt; h++)
			{
				setTile(w, l, h, 2);
			}
			if (getTile(w, l, 0) == 0)
				setTile(w, l, 0, 1);
		}
}

attrib World::getTileAttrib(int x, int y, int z)
{
	if (x >= 0 && x < width && y >= 0 && y < length && z >= 0 && z < height)
		return tiles[x][y][z].getAttrib();
	return { 0, 0, 0, 0, 0, 0 };
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

char World::getTile(int x, int y, int z)
{
	if (x >= 0 && x < width && y >= 0 && y < length && z >= 0 && z < height)
		return  tiles[x][y][z].getID();
	return -1;
}

void World::setTile(int x, int y, int z, int id)
{
	if (x >= 0 && x < width && y >= 0 && y < length && z >= 0 && z < height)
		tiles[x][y][z].setID(id);
}