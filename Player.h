#pragma once
#include "SFML.h"
#include "Keyboard.h"
#include "World.h"
#include "Tile.h"
#include "TileAttrib.h"


class Player
{
public:
	sf::Vector3f getPosition();
	void setPosition(double x, double y, double z);
	int isInPortal(int);
	void update(Keyboard&, World&, int code, TileAttrib&);
	double getWidth();

	int portalCD = 0;
private:
	bool isColliding(int, int, int, int, int, int, World&, TileAttrib&);
	int getFriction(int, int, int, int, World&, TileAttrib&);

	int inBlock = -1, onBlock = -1, unBlock = -1;
	double posx = 0, posy = 0, posz = 0, width = 0.6;
	double posxOld = 0, posyOld = 0, poszOld = 0;
	double velx = 0, vely = 0, maxSpeed = 2, step = 0.1;
};

