#include "Render.h"


void Renderer::render(sf::RenderWindow& window, World& world, Player& player, int tileSize, int renderDist, std::vector<sf::Texture>& textures, TileAttrib &tileAtt, int ticks)
{
	int hgt, id, lvl = 112 / (world.getHeight() - 1), base = 144,
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
						rect.setFillColor(sf::Color(base + lvl * hgt, base + lvl * hgt, base + lvl * hgt));
						if (tileAtt.getAttrib(id).decor)
							rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx,
								window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125 - tileSize * 0.25);
						else
							rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx,
								window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125);
						window.draw(rect);
					}
					if (tileAtt.getAttrib(world.getTile(w, l, h)).transparent)
						if (tileAtt.getAttrib(world.getTile(w, l - 1, h)).side)
						{
							id = world.getTile(w, l - 1, h);
							if (!tileAtt.getAttrib(id).invisible)
							{
								rect.setTextureRect(sf::IntRect((((ticks / 30) % (textures[id * 2].getSize().x) / 32)) * 32, 0, 32, 4));
								rect.setTexture(&textures[id * 2.0]);
								if (tileAtt.getAttrib(id).decor)
									rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx,
										window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125 - tileSize * 0.25);
								else
									rect.setPosition(window.getSize().x / 2.0 + double(w) * tileSize - posx,
										window.getSize().y / 2.0 + double(l) * tileSize - posy - double(h) * tileSize * 0.125 + posz * tileSize * 0.125);
								rect.setSize(sf::Vector2f(tileSize, tileSize * 0.125));
								rect.setFillColor(sf::Color(base + lvl * hgt, base + lvl * hgt, base + lvl * hgt));
								window.draw(rect);
							}
						}
					if ((int(player.getPosition().x / tileSize) + 1 == world.getWidth() || int(player.getPosition().y / tileSize) + 1 == world.getLength()) || (int(player.getPosition().x / tileSize) + 1 == w && int(player.getPosition().y / tileSize) + 1 == l) && player.getPosition().z - 0 == h)
					{
						rect.setTexture(&textures[1]);
						rect.setFillColor(sf::Color(base + lvl * player.getPosition().z, base + lvl * player.getPosition().z, base + lvl * player.getPosition().z));
						rect.setSize(sf::Vector2f(player.getWidth() * tileSize, player.getWidth() * tileSize));
						rect.setPosition(window.getSize().x / 2.0 - player.getWidth() / 2.0 * tileSize, window.getSize().y / 2.0 - player.getWidth() / 2.0 * tileSize);
						window.draw(rect);
					}
				}
			}
		}
	}
}