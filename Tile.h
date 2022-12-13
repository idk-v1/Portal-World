#pragma once

struct attrib
{
	char frict = 3, damage = 0, light = 0, dropID = 0;
	bool isSolid = true, isTransparent = false;
};

class Tile
{
public:
	void setID(char);
	char getID();
	attrib getAttrib();
private:
	char id = 0;
};