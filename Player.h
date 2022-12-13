#pragma once
#include "SFML.h"
#include "Keyboard.h"
#include "World.h"
#include "Tile.h"


class Player
{
public:
	Player(double, double, double);

	sf::Vector3f getPosition();

	void update(Keyboard&, World&, int);
	double getWidth();
private:
	bool isColliding(int, int, int, int, int, int, World&);
	int getFriction(int, int, int, int, World&);

	double posx, posy, posz, width = 0.6;
	double velx = 0, vely = 0, maxSpeed = 2, step = 0.1;
};

