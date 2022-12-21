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

		"dirtSide.png",
		"grassTop.png",

		"dirtSide.png",
		"dirtTop.png",

		"sandSide.png",
		"sandTop.png",

		"NONE",
		"portalTop.png",

		"stoneSide.png",
		"stoneTop.png",

		"iceSide.png",
		"iceTop.png",

		"treeSide.png",
		"treeTop.png",

		"bricksSide.png",
		"bricksTop.png",

		"NONE",
		"NONE"
	};
};