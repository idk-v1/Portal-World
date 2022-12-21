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

void Keyboard::getClick(int code, bool isDown)
{
	switch (code)
	{
	case l:
		lc = isDown;
		break;
	case r:
		rc = isDown;
	}
}
