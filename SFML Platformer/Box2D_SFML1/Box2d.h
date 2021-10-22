#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#pragma once

class Box2d
{
private:
	b2BodyDef* m_bodyDef;
	b2PolygonShape* m_polyShape;
	b2FixtureDef* m_fix;
	b2Body* m_body;

	sf::RectangleShape* m_rect;

	float m_Scale;

public:
	Box2d(b2World* m_world, const float& _scale, sf::RectangleShape* _rect, b2Vec2 _pos, bool _isDynamic = false);
	~Box2d();

	void SetVelocity(b2Vec2 _vel)	{ m_body->SetLinearVelocity(_vel);		};
	b2Vec2 GetVelocity()			{ return m_body->GetLinearVelocity();	};

	void Update();
};