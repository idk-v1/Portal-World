#include "Tile.h"

void Tile::setID(int tileID)
{
	id = tileID;
}

int Tile::getID()
{
	return id;
}

attrib Tile::getAttrib()
{
	attrib att;
	switch (id)
	{
	case 0:
		att.frict = 0;
		att.isSolid = false;
		att.isTransparent = true;
		break;
	case 1:
		att.frict = 7;
		att.isSolid = false;
		att.isTransparent = true;
		break;
	case 2:
		att.dropID = 2;
		break;
	case 3:
		att.dropID = 3;
		break;
	}
	return att;
}