#pragma once
#include "SFML.h"
#include <vector>

class TexManager
{
public:
	void load(std::vector<sf::Texture>&);
private:
	std::vector<std::string>textures = 
	{
		"WaterSide.png",
		"WaterTop.png",

		"GrassSide.png",
		"GrassTop.png",

		"SandSide.png",
		"SandTop.png",

		"PlayerSide.png",
		"PlayerTop.png"
	};
};