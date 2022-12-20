#pragma once

enum keys
{
	a = 0,
	d = 3,
	s = 18,
	w = 22,
	e = 4
};

class Keyboard
{
public:
	void getKeys(int, bool);
	bool wk = false, ak = false, sk = false, dk = false, ek = false;
};

