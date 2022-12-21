#include "Tile.h"

void Tile::setID(int tileID)
{
	id = tileID;
}

int Tile::getID()
{
	return id;
}

int Tile::getBiome()
{
	return biome;
}

void Tile::setBiome(int biomeId)
{
	biome = biomeId;
}