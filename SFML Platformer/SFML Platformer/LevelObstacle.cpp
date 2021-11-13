#include "LevelObstacle.h"
#include <iostream>

LevelObstacle::LevelObstacle(sf::Vector2f _dimensions, b2Vec2 _pos, b2World* _world, const float& _scale, const bool& _kill)
{
	isDangerous = _kill;
	tag = _kill ? Tag::LevelObstacleKill : Tag::LevelObstacle;

	m_colliderBounds = new sf::RectangleShape(_dimensions);
	m_colliderBounds->setOrigin(_dimensions.x / 2, _dimensions.y / 2);

	if (_kill)
	{
		m_colliderBounds->setFillColor(sf::Color::Red);

		m_colliderBounds->setPosition(sf::Vector2f(_pos.x, _pos.y));
		box2d = nullptr;
	}
	else
	{
		if (!m_texture->loadFromFile("sprites/wall.png"))
		{
			std::cout << "Error loading wall sprite\n";
		}
		m_texture->setRepeated(true);

		m_colliderBounds->setTexture(m_texture);
		m_colliderBounds->setTextureRect(sf::IntRect(0, 0, m_colliderBounds->getGlobalBounds().width * 2, m_colliderBounds->getGlobalBounds().height));

		box2d = new Box2d(_world, _scale, m_colliderBounds, _pos);
	}
}

LevelObstacle::~LevelObstacle()
{
}