#include "Engine.h"
#include <iostream>


Engine::Engine(int width, int height)
{
	window.create(sf::VideoMode(width, height), "Tiles");
    window.setFramerateLimit(60);
    renderDist = std::max(window.getSize().x / tileSize / 2, window.getSize().y / tileSize / 2) + 1;
    std::cout << renderDist;
}

void Engine::start()
{
    worlds.push_back(World(250, 50, 7));
    players.push_back(Player(25 * tileSize, 25 * tileSize, 7));

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
                wk = 0; ak = 0; sk = 0; dk = 0;
                break;
            case sf::Event::KeyPressed:
                if (focus)
                    getKeys(event, 1);
                break;
            case sf::Event::KeyReleased:
                if (focus)
                    getKeys(event, 0);
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
            //update();
            //move();
        }

        window.clear();
        for (int p = 0; p < players.size(); p++)
            render.render(window, worlds[activeWorld], players[p], tileSize);
        window.display();
    }
}

void Engine::getKeys(sf::Event event, bool down)
{
    switch (event.key.code)
    {
    case 22:
        wk = down;
        break;
    case 00:
        ak = down;
        break;
    case 18:
        sk = down;
        break;
    case 03:
        dk = down;
        break;
    }
}