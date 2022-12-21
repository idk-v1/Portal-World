#pragma once


class Tile
{
public:
	void setID(int);
	int getID();
	int getBiome();
	void setBiome(int);
private:
	int id = 0, biome = 0;
};