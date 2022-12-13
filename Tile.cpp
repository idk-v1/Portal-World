#include "Tile.h"

void Tile::setID(char tileID)
{
	id = tileID;
}

char Tile::getID()
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
		att.frict = 5;
		att.isSolid = false;
		att.isTransparent = true;
		break;
	case 2:
		att.dropID = 2;
	}
	return att;
}