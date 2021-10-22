#include <iostream>
#include "Box2d.h"
#include "Object.h"

#pragma once

class Obstacle : public Object
{
private:
	Box2d* box2d;

public:

	Obstacle(b2Vec2 _pos, b2World* m_world, const float& _scale);
	~Obstacle();

	void Update();

	Box2d* GetB2d()	{ return box2d; };
};