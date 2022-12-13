#include "Keyboard.h"

void Keyboard::getKeys(int codep, bool isDownp)
{
	switch (codep)
	{
	case 22:
		wk = isDownp;
		break;
	case 0:
		ak = isDownp;
		break;
	case 18:
		sk = isDownp;
		break;
	case 3:
		dk = isDownp;
		break;
	}
}