#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Box2d.h"
#include "Object.h"

#pragma once

class LevelObstacle : public Object
{
private:
	bool isDangerous;

public:
	LevelObstacle(sf::Vector2f _dimensions, b2Vec2 _pos, b2World* _world, const float& _scale, const bool& _kill = false);
	~LevelObstacle();

	bool IsDangerous()	{ return isDangerous; };
};