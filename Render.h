#pragma once
#include "World.h"
#include "Player.h"
#include "SFML.h"

class Renderer
{
public:
	void render(sf::RenderWindow&, World&, Player&, int);
private:
	sf::RectangleShape rect;
};

