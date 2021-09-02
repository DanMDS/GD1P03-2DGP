#include <iostream>
#include "Level.h"

Level::Level()
{
	if (!canvasTexture.loadFromFile("levels/test 1.png"))
	{
		std::cout << "Error: Loading level 1 image";
	}
}

Level::~Level()
{

}

// Write function to increment test levels