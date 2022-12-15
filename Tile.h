#pragma once

struct attrib
{
	int frict = 2, damage = 0, light = 0, dropID = 0;
	bool isSolid = true, isTransparent = false, isDecor = false;
};

class Tile
{
public:
	void setID(int);
	int getID();
	attrib getAttrib();
private:
	int id = 0, biome;
};