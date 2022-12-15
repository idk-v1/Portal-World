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
    renderDist = std::max(window.getSize().x / tileSize / 2, window.getSize().y / tileSize / 2) + 1;

    texManager.load(textures);

    worlds.push_back(World(250, 50, 10, rand()));
    players.push_back(Player(5 * tileSize, 5 * tileSize, 10));

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
            for (int p = 0; p < players.size(); p++)
            {
                players[p].update(keyboard, worlds[activeWorld], tileSize);
                if (worlds[activeWorld].getTile(
                    players[p].getPosition().x / tileSize,
                    players[p].getPosition().y / tileSize,
                    players[p].getPosition().z) == 4 || 
                    worlds[activeWorld].getTile(
                    players[p].getPosition().x / tileSize,
                    players[p].getPosition().y / tileSize,
                    players[p].getPosition().z + 1) == 4)
                {
                    worlds.push_back(World(100, 50, 7, rand()));
                    activeWorld = worlds.size() - 1;
                    players[p] = Player(5 * tileSize, 5 * tileSize, 5);
                }
            }
        }

        window.clear();
        for (int p = 0; p < players.size(); p++)
            render.render(window, worlds[activeWorld], players[p], tileSize, renderDist, textures);
        window.display();
    }
}