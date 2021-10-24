#include "LevelObstacle.h"
#include <iostream>

LevelObstacle::LevelObstacle(sf::Vector2f _dimensions, b2Vec2 _pos, b2World* _world, const float& _scale)
{
	tag = "levelObstacle";

	m_colliderBounds = new sf::RectangleShape(_dimensions);
	m_colliderBounds->setOrigin(_dimensions.x / 2, _dimensions.y / 2);
	m_colliderBounds->setFillColor(sf::Color::Green);
	m_colliderBounds->setOutlineColor(sf::Color::Blue);
	m_colliderBounds->setOutlineThickness(1);

	box2d = new Box2d(_world, _scale, m_colliderBounds, _pos);
}

LevelObstacle::~LevelObstacle()
{
}

void LevelObstacle::Update()
{
	m_sprite->setPosition(m_colliderBounds->getPosition());
	m_sprite->setRotation(m_colliderBounds->getRotation());
	box2d->Update();
}
