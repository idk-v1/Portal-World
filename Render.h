#pragma once
#include "World.h"
#include "Player.h"
#include "SFML.h"
#include "Tile.h"
#include <vector>

class Renderer
{
public:
	void render(sf::RenderWindow&, World&, Player&, int, std::vector<sf::Texture>&);
private:
	sf::RectangleShape rect;
};