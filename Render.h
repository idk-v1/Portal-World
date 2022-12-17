#pragma once
#include "World.h"
#include "Player.h"
#include "SFML.h"
#include "Tile.h"
#include "TileAttrib.h"
#include <vector>

class Renderer
{
public:
	void render(sf::RenderWindow&, World&, Player&, int, int, std::vector<sf::Texture>&, TileAttrib&, int);
private:
	sf::RectangleShape rect;
};