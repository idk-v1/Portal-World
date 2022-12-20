#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


struct attribute
{
	std::string name = "ERR";
	int id = -1, drop = -1, frict = 0, light = 0;
	bool invisible = true, transparent = true, decor = false, side = false, solid = false, liquid = false, replacable = false, breakable = false;
};


class TileAttrib
{
public:
	void load(std::string);
	attribute getAttrib(int);
	int getSize();

private:
	std::ifstream file;
	std::string data;
	std::vector<attribute>attribs;
};