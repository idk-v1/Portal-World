#include "Render.h"


void Renderer::render(sf::RenderWindow& window, World& world, Player& player, int tileSize, int renderDist, std::vector<sf::Texture>& textures)
{
	int hgt, id, idBack, lvl = 128 / (world.getHeight() - 1),
		posx = player.getPosition().x, posy = player.getPosition().y, posz = player.getPosition().z;

	for (int w = -renderDist + posx / tileSize; w <= renderDist + posx / tileSize; w++)
	{
		for (int l = -renderDist + posy / tileSize; l <= renderDist + posy / tileSize; l++)
		{
			if (w >= 0 && w < world.getWidth() && l >= 0 && l < world.getLength())
			{
				hgt = 0;
				for (int h = 0; h < world.getHeight(); h++)
					if (world.getTile(w, l, h) > 0)
						hgt = h;
				for (int h = 0; h < world.getHeight(); h++)
				{
					id = world.getTile(w, l, h);
					if (hgt == h)
					{
						rect.setSize(sf::Vector2f(tileSize, tileSize));
						rect.setTexture(&textures[id * 2.0 + 1]);
						rect.setTextureRect(sf::IntRect(0, 0, 32, 32));
						rect.setFillColor(sf::Color(128 + lvl * hgt, 128 + lvl * hgt, 128 + lvl * hgt));
						rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx,
							window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125);
						window.draw(rect);
					}
					if (world.getTileAttrib(w, l, h).isTransparent)
						if (world.getTileAttrib(w, l - 1, h).isSolid)
						{
							id = world.getTile(w, l - 1, h);
							rect.setTextureRect(sf::IntRect(0, 0, 32, 4));
							rect.setTexture(&textures[id * 2.0]);
							rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx, window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125);
							rect.setSize(sf::Vector2f(tileSize, tileSize * 0.125));
							rect.setFillColor(sf::Color(128 + lvl * hgt, 128 + lvl * hgt, 128 + lvl * hgt));
							window.draw(rect);
						}
				}
			}
		}
	}
	rect.setTexture(&textures[1]);
	rect.setFillColor(sf::Color(96 + lvl * player.getPosition().z, 96 + lvl * player.getPosition().z, 96 + lvl * player.getPosition().z));
	rect.setSize(sf::Vector2f(player.getWidth() * tileSize, player.getWidth() * tileSize));
	rect.setPosition(window.getSize().x / 2.0 - player.getWidth() / 2.0 * tileSize, window.getSize().y / 2.0 - player.getWidth() / 2.0 * tileSize);
	window.draw(rect);
}