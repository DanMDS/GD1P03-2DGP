#include "LevelObstacle.h"
#include <iostream>

LevelObstacle::LevelObstacle(b2Vec2 _pos, b2World* _world, const float& _scale)
{
	if (!m_texture->loadFromFile("sprites/platform.png"))
	{
		std::cout << "Error: loading texture";
	}
	m_sprite->setTexture(*m_texture);
	m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2));

	m_colliderBounds = new sf::RectangleShape(sf::Vector2f(m_sprite->getGlobalBounds().width, m_sprite->getGlobalBounds().height));
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
