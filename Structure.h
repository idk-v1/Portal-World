#pragma once
#include <string>
#include <vector>
#include "SFML.h"


class Structure
{
public:
	Structure(std::string);
	int getTile(int, int, int);
	int getWidth();
	int getLength();
private:
	std::vector<std::vector<std::vector<int>>>tiles;
};