#include "Player.h"


Player::Player(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

sf::Vector3f Player::getPosition()
{
	return sf::Vector3f(x, y, z);
}
