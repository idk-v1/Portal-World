#include "Render.h"


void Renderer::render(sf::RenderWindow &window, World &world, Player &player, int tileSize)
{
	int hgt, id, idBack, lvl = 128 / (world.getHeight() - 1),
		posx = player.getPosition().x, posy = player.getPosition().y, posz = player.getPosition().z;
	bool draw;

	rect.setSize(sf::Vector2f(tileSize, tileSize));

	for (int w = 0; w < world.getWidth(); w++)
	{
		for (int l = 0; l < world.getLength(); l++)
		{
			hgt = 0;
			for (int h = 0; h < world.getHeight(); h++)
				if (world.getTile(w, l, h) > 0)
					hgt = h;
			for (int h = 0; h < world.getHeight(); h++)
			{
				draw = true;
				id = world.getTile(w, l, h);
				if (id < 1)
					draw = false;
				if (true)
				{
					rect.setFillColor(sf::Color(128 + lvl * hgt, 128 + lvl * hgt, 128 + lvl * hgt));
					rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx, window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125);
					window.draw(rect);
				}
			}
		}
	}
	rect.setFillColor(sf::Color(255, 0, 0));
	rect.setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
	window.draw(rect);
}