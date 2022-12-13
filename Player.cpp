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
    velx += (double(keyboard.dk) - double(keyboard.ak)) * 0.0025 * tileSize;
    vely += (double(keyboard.sk) - double(keyboard.wk)) * 0.0025 * tileSize;

    if (velx >= maxSpeed) velx = maxSpeed;
    if (velx <= -maxSpeed) velx = -maxSpeed;
    if (vely >= maxSpeed) vely = maxSpeed;
    if (vely <= -maxSpeed) vely = -maxSpeed;

    // Move Down
    if (!isColliding(-1, -1, posz - 1, 0, 0, tileSize, world) &&
        !isColliding(1, -1, posz - 1, 0, 0, tileSize, world) &&
        !isColliding(1, 1, posz - 1, 0, 0, tileSize, world) &&
        !isColliding(-1, 1, posz - 1, 0, 0, tileSize, world) &&
        posz > 0)
    {
        std::cout << "Down: " << posz << "\n";
        posz--;
    }

    // Move Up
    if (isColliding(-1, -1, posz, 0, 0, tileSize, world) ||
        isColliding(1, -1, posz, 0, 0, tileSize, world) ||
        isColliding(1, 1, posz, 0, 0, tileSize, world) ||
        isColliding(-1, 1, posz, 0, 0, tileSize, world))
    {
        std::cout << "Up: " << posz << "\n";
        posz++;
    }

    velx /= double(10 + world.getTileAttrib(posz, posx / tileSize, posy / tileSize).frict) / 9.5;
    vely /= double(10 + world.getTileAttrib(posz, posx / tileSize, posy / tileSize).frict) / 9.5;

    // Move Right
    if (velx > 0)
        for (int i = 0; i < std::abs(velx) / step; i++)
            if (!isColliding(1,  1, posz + 1, step, 0, tileSize, world) &&
                !isColliding(1, -1, posz + 1, step, 0, tileSize, world))
                posx += step;
            else
                velx = 0;

    // Move Left
    if (velx < 0)
        for (int i = 0; i < std::abs(velx) / step; i++)
            if (!isColliding(-1,  1, posz + 1, -step, 0, tileSize, world) &&
                !isColliding(-1, -1, posz + 1, -step, 0, tileSize, world))
                posx -= step;
            else
                velx = 0;

    //// BOTTOM
    //if (vely > 0)
    //    for (int i = 0; i < std::abs(vely) * 100; i++)
    //        if (isTileMovable(posh + 1, (posx - playWidth / 2 * tileSize) / tileSize, (posy + playWidth / 2 * tileSize + step) / tileSize) &&
    //            isTileMovable(posh + 1, (posx + playWidth / 2 * tileSize) / tileSize, (posy + playWidth / 2 * tileSize + step) / tileSize))
    //            posy += step;
    //        else
    //            vely = 0;

    //// TOP
    //if (vely < 0)
    //    for (int i = 0; i < std::abs(vely) * 100; i++)
    //        if (isTileMovable(posh + 1, (posx - playWidth / 2 * tileSize) / tileSize, (posy - playWidth / 2 * tileSize - step) / tileSize) &&
    //            isTileMovable(posh + 1, (posx + playWidth / 2 * tileSize) / tileSize, (posy - playWidth / 2 * tileSize - step) / tileSize))
    //            posy -= step;
    //        else
    //            vely = 0;

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
    return world.getTileAttrib(z, (posx + dirx * width / 2 * tileSize - offx) / tileSize, (posy + diry * width / 2 * tileSize - offy) / tileSize).isSolid;
}