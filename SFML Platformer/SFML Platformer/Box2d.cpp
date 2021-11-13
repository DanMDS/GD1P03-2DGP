#include "Box2d.h"
#include <iostream>

Box2d::Box2d(b2World* _world, const float& _scale, sf::RectangleShape* _rect, b2Vec2 _pos, bool _isDynamic)
{
	m_Scale = _scale;
	m_rect = _rect;

	m_world = _world;

	m_bodyDef = new b2BodyDef();
	m_polyShape = new b2PolygonShape();
	m_fix = new b2FixtureDef();

	m_bodyDef->position = b2Vec2(_pos.x / _scale, _pos.y / _scale);
	m_bodyDef->type = (_isDynamic) ? b2_dynamicBody : b2_kinematicBody;
	m_body = _world->CreateBody(m_bodyDef);

	m_polyShape->SetAsBox((_rect->getGlobalBounds().width / 2) / _scale, (_rect->getGlobalBounds().height / 2) / _scale);

	m_fix->density = 1.f;
	m_fix->shape = m_polyShape;
	m_body->CreateFixture(m_fix);

	Update();
}

Box2d::~Box2d()
{
	m_world->DestroyBody(m_body);
	delete m_bodyDef;
	delete m_polyShape;
	delete m_fix;

	m_bodyDef = nullptr;
	m_polyShape = nullptr;
	m_fix = nullptr;
	m_body = nullptr;
}

void Box2d::Update()
{
	m_rect->setPosition(m_body->GetPosition().x * m_Scale, m_body->GetPosition().y * m_Scale);
	m_rect->setRotation(m_body->GetAngle() * 180 / b2_pi);
}
