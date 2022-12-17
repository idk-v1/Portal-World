#include "World.h"
#include <iostream>


World::World(int seed, int id, bool isDef, int portalLocT, int portalLocB)
{
	this->id = id;
	this->seed = seed;
	this->portalLocT = portalLocT;
	this->portalLocB = portalLocB;

	noise.setSeed(seed);

	if (isDef)
		genDefault();
	else
	{
		switch (std::hash<int>{}(seed + 5) % 3)
		{
		case 0:
			genIslands();
			break;
		case 1:
			genHills();
			break;
		case 2:
			genRand();
			break;
		}
	}
	genPortal();
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

int World::getID()
{
	return id;
}


void World::genPortal()
{
	int hgt;
	if (portalLocT >= width || portalLocT < 0)
		portalLocT = std::hash<int>{}(seed) % width;
	if (portalLocB >= width || portalLocB < 0)
		portalLocB = std::hash<int>{}(seed + 1) % width;

	hgt = 1;
	for (int h = 0; h < height; h++)
		if (getTile(portalLocT, 0, h) != 0)
			hgt = h + 1;
	setTile(portalLocT, 0, hgt, 5);
	std::cout << "Portal is at: X: " << portalLocT << " Y: 0\n";

	hgt = 1;
	for (int h = 0; h < height; h++)
		if (getTile(portalLocB, length - 1, h) != 0)
			hgt = h + 1;
	setTile(portalLocB, length - 1, hgt, 5);
	std::cout << "Portal is at: X: " << portalLocB << " Y: " << length - 1 << "\n";
}

void World::genDefault()
{
	int hgt;
	std::vector<std::vector<Tile>> vvt;
	std::vector<Tile> vt;
	Tile t;

	width = 250;
	length = 50;
	height = 10;

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
					setTile(w, l, 0, 4);
		}
}

void World::genIslands()
{
	int hgt;
	std::vector<std::vector<Tile>> vvt;
	std::vector<Tile> vt;
	Tile t;

	width = 250;
	length = 50;
	height = 10;

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
					setTile(w, l, 0, 4);
		}
}

void World::genHills()
{
	int hgt;
	std::vector<std::vector<Tile>> vvt;
	std::vector<Tile> vt;
	Tile t;

	width = 250;
	length = 50;
	height = 10;

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
			hgt = pow(height - 2 - std::floor(pow(noise.unsignedFBM(w * 0.025, l * 0.025, 2, 0.1, 0.15) * (height - 1.0), 3) / (height - 1.0) + 0.75) / (height - 1.0), 1.2) - height / 3;
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
					setTile(w, l, 0, 4);
		}
}

void World::genRand()
{
	int hgt;
	std::vector<std::vector<Tile>> vvt;
	std::vector<Tile> vt;
	Tile t;

	width = 250;
	length = 50;
	height = 10;

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
			hgt = rand() % (height - 5) + 1;
			for (int h = 0; h < hgt; h++)
			{
				switch (rand() % 4)
				{
				case 0:
					setTile(w, l, h, 1);
					break;
				case 1:
					setTile(w, l, h, 2);
					break;
				case 2:
					setTile(w, l, h, 3);				
					break;
				case 3:
					setTile(w, l, h, 4);
				}
			}
		}
}