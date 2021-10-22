#include <iostream>
#include "Box2d.h"
#include "Object.h"

#pragma once

class Player : public Object
{
private:
	Box2d* box2d;
	bool m_grounded;
	float m_jumpPower;
	float m_speed;
	float m_speedMax;
	float m_speedInc;

public:

	Player(b2Vec2 _pos, b2World* m_world, const float& _scale);
	~Player();

	void Update();
	void Jump(float _power);
	void Move(float _speed);
	void PlayerControls(bool _grounded);

	void SetGrounded(bool _bool)	{ m_grounded = _bool;	};

	Box2d* GetB2d()					{ return box2d;			};
};