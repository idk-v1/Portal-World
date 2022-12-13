#include "Player.h"
#include <iostream>


Player::Player(double x, double y, double z)
{
	posx = x;
	posy = y;
	posz = z;
}

sf::Vector3f Player::getPosition()
{
	return sf::Vector3f(posx, posy, posz);
}

void Player::update(Keyboard& keyboard, World &world, int tileSize)
{
    int max;
    max = std::max(getFriction(-1, -1, posz - 1, tileSize, world), getFriction(1, -1, posz - 1, tileSize, world));
    max = std::max(getFriction( 1,  1, posz - 1, tileSize, world), max);
    max = std::max(getFriction(-1,  1, posz - 1, tileSize, world), max);
    max = std::max(getFriction( 0,  0, posz, tileSize, world), max);
    double frict = 1 + 0.1 * max;

    velx += (double(keyboard.dk) - double(keyboard.ak)) * 0.025 * tileSize;
    vely += (double(keyboard.sk) - double(keyboard.wk)) * 0.025 * tileSize;

    velx /= frict;
    vely /= frict;

    // DOWN
    if (!isColliding(-1, -1, posz - 1, 0, 0, tileSize, world) &&
        !isColliding( 1, -1, posz - 1, 0, 0, tileSize, world) &&
        !isColliding( 1,  1, posz - 1, 0, 0, tileSize, world) &&
        !isColliding(-1,  1, posz - 1, 0, 0, tileSize, world) &&
        posz > 0)
        posz--;

    // UP
    if (isColliding(-1, -1, posz, 0, 0, tileSize, world) ||
        isColliding( 1, -1, posz, 0, 0, tileSize, world) ||
        isColliding( 1,  1, posz, 0, 0, tileSize, world) ||
        isColliding(-1,  1, posz, 0, 0, tileSize, world))
        posz++;

    // RIGHT
    if (velx > 0)
        for (int i = 0; i < std::abs(velx) * 10; i++)
            if (!isColliding( 1, -1, posz + 1,  step, 0, tileSize, world) &&
                !isColliding( 1,  1, posz + 1,  step, 0, tileSize, world))
                posx += step;
            else
            {
                velx = 0;
                posx -= step;
            }

    // LEFT
    if (velx < 0)
        for (int i = 0; i < std::abs(velx) * 10; i++)
            if (!isColliding( -1, -1, posz + 1, -step, 0, tileSize, world) &&
                !isColliding( -1,  1, posz + 1, -step, 0, tileSize, world))
                posx -= step;
            else
            {
                velx = 0;
                posx += step;
            }

    // BOTTOM
    if (vely > 0)
        for (int i = 0; i < std::abs(vely) * 10; i++)
            if (!isColliding(-1,  1, posz + 1, 0,  step, tileSize, world) &&
                !isColliding( 1,  1, posz + 1, 0,  step, tileSize, world))
                posy += step;
            else
            {
                vely = 0;
                posy -= step;
            }

    // TOP
    if (vely < 0)
        for (int i = 0; i < std::abs(vely) * 10; i++)
            if (!isColliding(-1, -1, posz + 1, 0, -step, tileSize, world) &&
                !isColliding( 1, -1, posz + 1, 0, -step, tileSize, world))
                posy -= step;
            else
            {
                vely = 0;
                posy += step;
            }

    if (std::abs(velx) < 0.01) velx = 0;
    if (std::abs(vely) < 0.01) vely = 0;

    if (posx + width / 2 * tileSize >= (double)world.getWidth() * tileSize) 
        posx = (double)world.getWidth() * tileSize - width / 2 * tileSize - 1;
    if (posy + width / 2 * tileSize >= (double)world.getLength() * tileSize) 
        posy = (double)world.getLength() * tileSize - width / 2 * tileSize - 1;
    if (posx - width / 2 * tileSize < 0) 
        posx = width / 2 * tileSize;
    if (posy - width / 2 * tileSize < 0) 
        posy = width / 2 * tileSize;
}

double Player::getWidth()
{
    return width;
}

bool Player::isColliding(int dirx, int diry, int z, int offx, int offy, int tileSize, World &world)
{
    return world.getTileAttrib((posx + dirx * width / 2 * tileSize + offx) / tileSize, 
        (posy + diry * width / 2 * tileSize + offy) / tileSize, z).isSolid;
}

int Player::getFriction(int dirx, int diry, int z, int tileSize, World &world)
{
    return world.getTileAttrib((posx + dirx * width / 2 * tileSize) / tileSize,
        (posy + diry * width / 2 * tileSize) / tileSize, z).frict;
}