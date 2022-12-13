#pragma once
#include "SFML.h"


class Player
{
public:
	Player(int, int, int);

	sf::Vector3f getPosition();
private:
	int x, y, z;
};

