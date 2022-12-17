#pragma once


class Tile
{
public:
	void setID(int);
	int getID();
private:
	int id = 0, biome = 0;
};