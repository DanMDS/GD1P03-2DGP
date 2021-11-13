#include <iostream>
#include "Box2d.h"
#include "Object.h"

#pragma once

class Player : public Object
{
private:
	bool m_grounded;
	float m_jumpPower;
	float m_speed;
	b2Vec2 m_explodeDir;
	float m_explodeDist;
	float m_explodeMag;
	b2Vec2 m_startPos;
	sf::CircleShape* m_trans;
	bool m_isDead;
	bool m_transDone;
	float m_maxSpeed;
	b2Vec2 m_posBoundsMax;
	b2Vec2 m_posBoundsMin;

	sf::Clock clock;
	sf::Time jumpTime;
	sf::Time shootTime;
	sf::Time levelTime;
	float m_jumpCooldown;
	float m_shootCooldown; // <-- not set yet

public:
	Player(b2Vec2 _pos, b2World* m_world, const float& _scale);
	~Player();

	void Update();
	void Jump(float _power);
	void Explode(sf::Vector2f _direction, float _power);
	void PlayerControls(bool _grounded);
	void Transition(bool _dead);

	void SetStartPos(b2Vec2 _pos, bool _checkpoint = false);

	void SetPosBounds(b2Vec2 _posA, b2Vec2 _posB)	{ m_posBoundsMin = _posA;	m_posBoundsMax = _posB;		};
	void SetGrounded(bool _bool)					{ m_grounded = _bool;									};

	bool isTransDone()								{ return m_transDone;									};
	bool IsDead()									{ return m_isDead;										};
	sf::CircleShape* GetTrans()						{ return m_trans;										};
	Box2d* GetB2d()									{ return box2d;											};
	b2Vec2 GetBodyPos()								{ return box2d->GetBody()->GetPosition();				};
};