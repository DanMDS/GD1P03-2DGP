#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Box2d.h"
#include "Object.h"

#pragma once

class LevelObstacle : public Object
{
private:
	Box2d* box2d;

public:
	LevelObstacle(b2Vec2 _pos, b2World* _world, const float& _scale);
	~LevelObstacle();

	void Update();
};