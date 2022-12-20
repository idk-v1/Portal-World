#include "Keyboard.h"

void Keyboard::getKeys(int code, bool isDown)
{
	switch (code)
	{
	case w:
		wk = isDown;
		break;
	case a:
		ak = isDown;
		break;
	case s:
		sk = isDown;
		break;
	case d:
		dk = isDown;
		break;
	case e:
		ek = isDown;
	}
}