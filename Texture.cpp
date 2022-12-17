#include "Texture.h"


void TexManager::load(std::vector<sf::Texture>&tex, TileAttrib &tileAtt)
{
    const unsigned int numPixels = 32 * 32;
    sf::Uint8 pixels[4 * numPixels];
    sf::Image missing, clear;
    sf::Texture missingTex, clearTex;

    for (int i = 0; i < numPixels; i++)
    {
        int xval = i % 32;
        int yval = i / 32;
        bool val = ((xval % 16 < 8 && yval % 16 < 8) || (xval % 16 >= 8 && yval % 16 >= 8));

        pixels[i * 4 + 0] = val * 255;
        pixels[i * 4 + 1] = 0;
        pixels[i * 4 + 2] = val * 255;
        pixels[i * 4 + 3] = 255;
    }
    missing.create(32, 32, pixels);
    missingTex.create(32, 32);
    missingTex.update(pixels);

    for (int i = 0; i < numPixels * 4; i++)
        pixels[i] = 255;
    clear.create(32, 32);
    clearTex.create(32, 32);
    clearTex.update(pixels);

    tex.push_back(missingTex);
    tex.push_back(clearTex);

	for (int i = 0; i < textures.size(); i++)
	{
		sf::Texture texture;
        if (textures[i] == "NONE")
            texture = clearTex;
        else if (!texture.loadFromFile("Portal_World/textures/" + textures[i]))
            texture = missingTex;
		tex.push_back(texture);
	}
}
