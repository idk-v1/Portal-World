#include "World.h"
#include <iostream>


World::World(int seed, int id, bool isDef, int portalLocT, int portalLocB, TileAttrib &att)
{
	this->id = id;
	this->seed = seed;
	this->portalLocT = portalLocT;
	this->portalLocB = portalLocB;

	noise.setSeed(seed);

	if (isDef)
		genDefault(att);
	else
	{
		switch (std::hash<int>{}(seed + 5) % 3)
		{
		case 0:
			genIslands(att);
			break;
		case 1:
			genHills(att);
			break;
		case 2:
			genRand(att);
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


void World::init()
{
	std::vector<std::vector<Tile>> vvt;
	std::vector<Tile> vt;
	Tile t;

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

	srand(time(NULL));
}

void World::decorate(TileAttrib &att)
{
	int hgt, rocks = 0;

	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
		{
			hgt = std::floor(pow(noise.unsignedFBM(w * 0.025, l * 0.025, 2, 0.1, 0.15) * (height - 1.0), 3) / (height - 1.0) + 0.75) / (height - 1.0);

			if (std::hash<int>{}(seed + ++rocks) % (width / (hgt + 5)) == 0 &&
				std::hash<int>{}(seed + ++rocks) % (length / (hgt + 5)) == 0 &&
				att.getAttrib(getTile(w, l, hgt - 2)).solid)
			{
				for (int h = -2; h < 0; h++)
					for (int x = -1; x < 2; x++)
						for (int y = -1; y < 2; y++)
							if (x == 0 || y == 0)
								setTile(w + x, l + y, hgt + h, 6);
				setTile(w, l, hgt, 6);
			}

			if (std::hash<int>{}(seed + 200 + ++rocks) % (width / (hgt + 25)) == 0 &&
				std::hash<int>{}(seed + 200 + ++rocks) % (length / (hgt + 25)) == 0 &&
				getTile(w, l, hgt - 2) == 2)
			{
				for (int h = 1; h < 5; h++)
					setTile(w, l, hgt + h, 8);
			}
		}
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

void World::genDefault(TileAttrib& att)
{
	int hgt,
		waterMat = 1, 
		groundMat = 3, 
		coverMat = 2;

	width = 250;
	length = 50;
	height = 10;

	init();

	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
		{
			hgt = std::floor(pow(noise.unsignedFBM(w * 0.025, l * 0.025, 2, 0.1, 0.15) * (height - 1.0), 3) / (height - 1.0) + 0.75) / (height - 1.0);
			for (int h = 0; h < hgt - 1; h++)
			{
				if (h == hgt - 2)
					setTile(w, l, h, coverMat);
				else
					setTile(w, l, h, groundMat);
				if (hgt > height - 4 && h < hgt - 3)
					setTile(w, l, h, 6);
			}
			if (getTile(w, l, 0) == 0)
				setTile(w, l, 0, waterMat);
		}
	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
			if (getTile(w, l, 0) == 2)
				for (int x = -1; x < 2; x++)
					for (int y = -1; y < 2; y++)
						if (getTile(w + x, l + y, 0) == 1)
							setTile(w, l, 0, 4);

	decorate(att);
}

void World::genIslands(TileAttrib& att)
{
	int hgt, waterMat, groundMat, coverMat;

	switch ((std::hash<int>{}(rand()) % 5))
	{
	case 0:
	case 1:
		waterMat = 7;
		break;
	case 2:
	case 3:
	case 4:
		waterMat = 1;
		break;
	}

	switch ((std::hash<int>{}(rand()) % 5))
	{
	case 0:
	case 1:
		groundMat = 6;
		break;
	case 2:
	case 3:
	case 4:
		groundMat = 3;
		break;
	}

	switch ((std::hash<int>{}(rand()) % 7))
	{
	case 0:
		groundMat = 6;
	case 1:
		coverMat = 6;
		break;
	case 2:
	case 3:
		coverMat = 3;
		break;
	case 4:
	case 5:
	case 6:
		coverMat = 2;
		break;
	}

	width = 250;
	length = 50;
	height = 10;

	init();

	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
		{
			hgt = std::floor(pow(noise.unsignedFBM(w * 0.025, l * 0.025, 2, 0.1, 0.15) * (height - 1.0), 3) / (height - 1.0) + 0.75) / (height - 1.0);
			for (int h = 0; h < hgt - 1; h++)
			{
				if (h == hgt - 2)
					setTile(w, l, h, coverMat);
				else
					setTile(w, l, h, groundMat);
				if (hgt > height - 4 && h < hgt - 3)
					setTile(w, l, h, 6);
			}
			if (getTile(w, l, 0) == 0)
				setTile(w, l, 0, waterMat);
		}
	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
			if (getTile(w, l, 0) == 2)
				for (int x = -1; x < 2; x++)
					for (int y = -1; y < 2; y++)
						if (getTile(w + x, l + y, 0) == 1)
							setTile(w, l, 0, 4);
	decorate(att);
}

void World::genHills(TileAttrib& att)
{
	int hgt, waterMat, groundMat, coverMat;

	switch ((std::hash<int>{}(rand()) % 5))
	{
	case 0:
	case 1:
		waterMat = 7;
		break;
	case 2:
	case 3:
	case 4:
		waterMat = 1;
		break;
	}

	switch ((std::hash<int>{}(rand()) % 5))
	{
	case 0:
	case 1:
		groundMat = 6;
		break;
	case 2:
	case 3:
	case 4:
		groundMat = 3;
		break;
	}

	switch ((std::hash<int>{}(rand()) % 7))
	{
	case 0:
		groundMat = 6;
	case 1:
		coverMat = 6;
		break;
	case 2:
	case 3:
		coverMat = 3;
		break;
	case 4:
	case 5:
	case 6:
		coverMat = 2;
		break;
	}

	width = 250;
	length = 50;
	height = 10;

	init();

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
	decorate(att);
}

void World::genRand(TileAttrib& att)
{
	int hgt, waterMat, groundMat, coverMat;

	switch ((std::hash<int>{}(rand()) % 5))
	{
	case 0:
	case 1:
		waterMat = 7;
		break;
	case 2:
	case 3:
	case 4:
		waterMat = 1;
		break;
	}

	width = 250;
	length = 50;
	height = 10;

	init();

	for (int w = 0; w < width; w++)
		for (int l = 0; l < length; l++)
		{
			hgt = rand() % (height - 5) + 1;
			if (hgt == 0)
				setTile(w, l, 0, 1);
			for (int h = 0; h < hgt; h++)
			{
				switch (rand() % 5)
				{
				case 0:
					setTile(w, l, h, 2);
					break;
				case 1:
					setTile(w, l, h, 3);				
					break;
				case 2:
					setTile(w, l, h, 4);
					break;
				case 3:
					setTile(w, l, h, 6);
					break;
				case 4:
					setTile(w, l, h, 7);
					break;
				}
			}
		}
}