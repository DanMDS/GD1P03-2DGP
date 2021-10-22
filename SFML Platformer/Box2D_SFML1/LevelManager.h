#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "LevelObstacle.h"

#pragma once

class LevelManager
{
private:
	int m_levelIndex;
	LevelObstacle* m_obstacle;

public:
	LevelManager();
	~LevelManager();
};