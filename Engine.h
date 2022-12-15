#pragma once
#include "SFML.h"
#include <chrono>
#include <vector>
#include "World.h"
#include "Render.h"
#include "Player.h"
#include"Keyboard.h"
#include "Texture.h"


class Engine
{
public:
	Engine(int, int);
	void start();
private:
	sf::RenderWindow window;
	bool focus = true;
	long now = 0, last = 0, ticks = 0, dt = 0;
	int tileSize = 48, fps = 1000 / 60, activeWorld = 0, renderDist;
	std::vector<World>worlds;
	Renderer render;
	std::vector<Player>players;
	Keyboard keyboard;
	std::vector<sf::Texture>textures;
	TexManager texManager;
};

