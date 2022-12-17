#include "Render.h"


void Renderer::render(sf::RenderWindow& window, World& world, Player& player, int tileSize, int renderDist, std::vector<sf::Texture>& textures, TileAttrib &tileAtt, int ticks)
{
	int hgt, id, lvl = 128 / (world.getHeight() - 1),
		posx = player.getPosition().x, posy = player.getPosition().y, posz = player.getPosition().z;

	for (int w = -renderDist + posx / tileSize; w <= renderDist + posx / tileSize; w++)
	{
		for (int l = -renderDist + posy / tileSize; l <= renderDist + posy / tileSize; l++)
		{
			if (w >= 0 && w < world.getWidth() && l >= 0 && l < world.getLength())
			{
				hgt = 0;
				for (int h = 0; h < world.getHeight(); h++)
					if (tileAtt.getAttrib(world.getTile(w, l, h)).solid || tileAtt.getAttrib(world.getTile(w, l, h)).liquid)
						hgt = h;
				for (int h = 0; h < world.getHeight(); h++)
				{
					id = world.getTile(w, l, h);
					if (hgt == h || (tileAtt.getAttrib(id).decor && !tileAtt.getAttrib(id).invisible))
					{
						rect.setSize(sf::Vector2f(tileSize, tileSize));
						rect.setTextureRect(sf::IntRect((ticks / 30) % (textures[id * 2 + 1].getSize().x / 32) * 32, 0, 32, 32));
						rect.setTexture(&textures[id * 2.0 + 1]);
						rect.setFillColor(sf::Color(128 + lvl * hgt, 128 + lvl * hgt, 128 + lvl * hgt));
						rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx,
							window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125);
						window.draw(rect);
					}
					if (tileAtt.getAttrib(world.getTile(w, l, h)).transparent)
						if (!tileAtt.getAttrib(world.getTile(w, l - 1, h)).decor)
						{
							id = world.getTile(w, l - 1, h);
							if (!tileAtt.getAttrib(id).invisible)
							{
								rect.setTextureRect(sf::IntRect((ticks / 30) % (textures[id * 2 + 1].getSize().x / 32) * 32, 0, 32, 4));
								rect.setTexture(&textures[id * 2.0]);
								rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx, window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125);
								rect.setSize(sf::Vector2f(tileSize, tileSize * 0.125));
								rect.setFillColor(sf::Color(128 + lvl * hgt, 128 + lvl * hgt, 128 + lvl * hgt));
								window.draw(rect);
							}
						}
					if ((floor(player.getPosition().x / tileSize) == w && floor(player.getPosition().y / tileSize) == l && player.getPosition().z - 1 == h) ||
						(ceil(player.getPosition().x / tileSize) == w && ceil(player.getPosition().y / tileSize) == l && player.getPosition().z - 1 == h) ||
						(floor(player.getPosition().x / tileSize) == w && ceil(player.getPosition().y / tileSize) == l && player.getPosition().z - 1 == h) ||
						(ceil(player.getPosition().x / tileSize) == w && floor(player.getPosition().y / tileSize) == l && player.getPosition().z - 1 == h))
					{
						rect.setTexture(&textures[1]);
						rect.setFillColor(sf::Color(96 + lvl * player.getPosition().z, 96 + lvl * player.getPosition().z, 96 + lvl * player.getPosition().z));
						rect.setSize(sf::Vector2f(player.getWidth() * tileSize, player.getWidth() * tileSize));
						rect.setPosition(window.getSize().x / 2.0 - player.getWidth() / 2.0 * tileSize, window.getSize().y / 2.0 - player.getWidth() / 2.0 * tileSize);
						window.draw(rect);
					}
				}
			}
		}
	}
}