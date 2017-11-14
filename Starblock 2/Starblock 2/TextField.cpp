#include "TextField.h"


#include "sfwdraw.h"


TextField::TextField()
{
	for (int i = 0; i < 260; ++i)
	{
		keysHeldDown[i] = false;
	}
	for (int i = 0; i < 260; ++i)
	{
		keysHeldDown[i] = false;
	}
	
	maxChars = 10;
}


TextField::~TextField()
{
}


void TextField::update()
{
	for (int i = 0; i < 260; ++i)
	{
		keysDown[i] = sfw::getKey(i) * !keysHeldDown[i];
		if (keysDown[i] && str.size() < maxChars && i <= 255)
		{
			str = str + (char)i;
		}
	}
	for (int i = 0; i < 260; ++i)
	{
		keysHeldDown[i] = sfw::getKey(i);
	}

	if (keysDown[259] && str.size() > 0)
	{
		str.erase(str.begin() + str.size() - 1);
	}

	if (keysDown[257])
	{
		callback();
	}
}

void TextField::reset()
{
	str = "";
	for (int i = 0; i < 256; ++i)
	{
		keysDown[i] = false;
	}
	for (int i = 0; i < 256; ++i)
	{
		keysHeldDown[i] = false;
	}
}

std::string TextField::getString()
{
	return str;
}

bool TextField::isKeyJustPressed(int key)
{
	if (key < 0 || key >= 256)
	{
		return 0;
	}
	else
	{
		return keysDown[key];
	}
}

bool TextField::isKeyPressed(int key)
{
	if (key < 0 || key >= 256)
	{
		return 0;
	}
	else
	{
		return keysHeldDown[key];
	}
}
