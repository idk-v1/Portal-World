#pragma once
#include "SFML.h"
#include "TileAttrib.h"
#include <vector>

class TexManager
{
public:
	void load(std::vector<sf::Texture>&, TileAttrib&);
private:
	std::vector<std::string>textures = 
	{
		"waterSideAn.png",
		"waterTopAn2.png",

		"grassSideAn.png",
		"grassTopAn.png",

		"dirtSide.png",
		"dirtTop.png",

		"sandSide.png",
		"sandTop.png",

		"NONE",
		"portalTop.png",

		"NONE",
		"NONE"
	};
};