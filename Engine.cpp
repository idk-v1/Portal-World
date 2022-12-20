#include "Engine.h"
#include <iostream>


Engine::Engine(int width, int height)
{
    window.create(sf::VideoMode(width, height), "Tiles");
    window.setFramerateLimit(60);

    srand(time(NULL));
}

void Engine::start()
{
    int otherWorld;

    renderDist = std::max(window.getSize().x / tileSize / 2, window.getSize().y / tileSize / 2) + 1;

    tileAtt.load("Portal_World/attrib/tileAttrib");
    texManager.load(textures, tileAtt);

    worlds.push_back(World(rand(), 1, true, 125, 125, tileAtt));
    player.setPosition(125 * tileSize, 25 * tileSize, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::GainedFocus:
                focus = true;
                break;
            case sf::Event::LostFocus:
                focus = false;
                break;
            case sf::Event::KeyPressed:
                if (focus)
                    keyboard.getKeys(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                if (focus)
                    keyboard.getKeys(event.key.code, false);
                break;
            case sf::Event::Resized:
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                renderDist = std::max(window.getSize().x / tileSize / 2, window.getSize().y / tileSize / 2) + 1;
                break;
            }
        }
        now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
        if (last == 0) last = now;
        dt += now - last;
        last = now;
        while (dt >= fps)
        {
            dt -= fps;
            ticks++;
            player.update(keyboard, worlds[activeWorld], tileSize, tileAtt);
            if (player.portalCD == 0)
            {
                if (player.isInPortal(tileSize) == -1)
                {
                    otherWorld = getWorldID(worlds[activeWorld].getID() - 1);
                    if (otherWorld != -1)
                    {
                        activeWorld = otherWorld;
                        player.setPosition(player.getPosition().x - tileSize, 1000 * tileSize, 10);
                        std::cout << "Load World: ";
                    }
                    else
                    {
                        worlds.push_back(World(rand(), worlds[activeWorld].getID() - 1, false, -1, player.getPosition().x / tileSize, tileAtt));
                        activeWorld = worlds.size() - 1;
                        player.setPosition(player.getPosition().x - tileSize, 1000 * tileSize, 10);
                        std::cout << "New World: ";
                    }
                    std::cout << worlds[activeWorld].getID() << "\n";
                }
                else if (player.isInPortal(tileSize) == 1)
                {
                    otherWorld = getWorldID(worlds[activeWorld].getID() + 1);
                    if (otherWorld != -1)
                    {
                        activeWorld = otherWorld;
                        player.setPosition(player.getPosition().x - tileSize, 0, 10);
                        std::cout << "Load World: ";
                    }
                    else
                    {
                        worlds.push_back(World(rand(), worlds[activeWorld].getID() + 1, false, player.getPosition().x / tileSize, -1, tileAtt));
                        activeWorld = worlds.size() - 1;
                        player.setPosition(player.getPosition().x - tileSize, 0, 10);
                        std::cout << "New World: ";
                    }
                    std::cout << worlds[activeWorld].getID() << "\n";
                }
            }
        }

        window.clear();
        render.render(window, worlds[activeWorld], player, tileSize, renderDist, textures, tileAtt, ticks);
        window.display();
    }
}

int Engine::getWorldID(int id)
{
    for (int i = 0; i < worlds.size(); i++)
        if (id == worlds[i].getID())
            return i;
    return -1;
}