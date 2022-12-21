#pragma once
#include "SFML.h"
#include <chrono>
#include <vector>
#include "World.h"
#include "Render.h"
#include "Player.h"
#include "Keyboard.h"
#include "Texture.h"
#include "TileAttrib.h"
#include "Structure.h"


class Engine
{
public:
	Engine(int, int);
	void start();
	TileAttrib tileAtt;
private:
	int getWorldID(int);

	sf::RenderWindow window;
	bool focus = true;
	long now = 0, last = 0, ticks = 0, dt = 0;
	int tileSize = 48, fps = 1000 / 60, activeWorld = 0, renderDist = 0;
	std::vector<World>worlds;
	Renderer render;
	Player player;
	Keyboard keyboard;
	std::vector<sf::Texture>textures;
	TexManager texManager;
	std::vector<Structure>structs;
	//sf::Text debug;
	//sf::Font font; 
};

