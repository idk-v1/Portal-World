#include "Structure.h"


Structure::Structure(std::string name)
{
	std::vector<std::vector<int>> vvi;
	std::vector<int> vi;
	int i;

	sf::Image data;
	if (data.loadFromFile("Portal_World/struct/" + name))
	{
		for (int x = 0; x < data.getSize().x; x++)
		{
			tiles.push_back(vvi);
			for (int y = 0; y < data.getSize().y; y++)
			{
				tiles[x].push_back(vi);
				for (int h = 0; h < 3; h++)
				{
					tiles[x][y].push_back(i);
				}
			}
		}

		for (int x = 0; x < data.getSize().x; x++)
			for (int y = 0; y < data.getSize().y; y++)
			{
				tiles[x][y][2] = data.getPixel(x, y).r;
				tiles[x][y][1] = data.getPixel(x, y).g;
				tiles[x][y][0] = data.getPixel(x, y).b;
			}
	}
}

int Structure::getTile(int x, int y, int z)
{
	if (x >= 0 && x < 16 && y >= 0 && y < 16 && z >= 0 && z < 3)
		return tiles[x][y][z];
	return -1;
}

int Structure::getWidth()
{
	return tiles.size();
}

int Structure::getLength()
{
	return tiles[0].size();
}
