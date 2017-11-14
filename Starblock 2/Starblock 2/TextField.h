#pragma once


#include <string>



class TextField
{
public:
	TextField();
	~TextField();

	int maxChars;
	void(*callback)();

	void update();
	void reset();
	std::string getString();
	bool isKeyJustPressed(int key);
	bool isKeyPressed(int key);

private:
	std::string str;

	bool keysDown[260];
	bool keysHeldDown[260];
};

