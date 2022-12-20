#include "TileAttrib.h"


void TileAttrib::load(std::string name)
{
	attribute att;
	int loc;
	std::string key, value;
	file.open(name);
	if (file.is_open())
	{
		while (std::getline(file, data))
		{
			for (int i = data.length() - 1; i >= 0; i--)
				if (data[i] == ' ')
					data.erase(i, 1);
			if (data == "}")
				attribs.push_back(att);
			else
			{
				loc = data.find(':');
				if (loc != std::string::npos)
				{
					key = data.substr(0, loc);
					value = data.substr(loc + 1, data.length() - loc + 1);
					if (value[0] == '"')
					{
						value.erase(value.length() - 1, 1);
						value.erase(0, 1);
					}

					if (key == "name")
						att.name = value;
					if (key == "id")
						att.id = stoi(value);
					if (key == "drop")
						att.drop = stoi(value);
					if (key == "frict")
						att.frict = stoi(value);
					if (key == "light")
						att.light = stoi(value);
					if (key == "invisible")
						att.invisible = stoi(value);
					if (key == "transparent")
						att.transparent = stoi(value);
					if (key == "decor")
						att.decor = stoi(value);
					if (key == "side")
						att.side = stoi(value);
					if (key == "solid")
						att.solid = stoi(value);
					if (key == "liquid")
						att.liquid = stoi(value);
					if (key == "replacable")
						att.replacable = stoi(value);
					if (key == "breakable")
						att.breakable = stoi(value);
				}
			}

		}
	}
	file.close();
}

attribute TileAttrib::getAttrib(int id)
{
	for (int i = 0; i < attribs.size(); i++)
		if (id == attribs[i].id)
			return attribs[i];
	return attribute();
}

int TileAttrib::getSize()
{
	return attribs.size();
}
