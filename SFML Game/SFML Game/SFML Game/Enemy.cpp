#include <iostream>
#include "Enemy.h"

Enemy::Enemy(sf::String _spritePath, sf::Vector2f _objPos)
{
	m_EnemyTexture = new sf::Texture();
	if (!m_EnemyTexture->loadFromFile(_spritePath))
	{
		std::cout << "Error: " << std::string(_spritePath) << " failed to load";
	}

	m_EnemySprite = new sf::Sprite();
	m_EnemySprite->setTexture(*m_EnemyTexture);

	m_EnemySprite->setOrigin(sf::Vector2f(m_EnemySprite->getLocalBounds().width / 2, m_EnemySprite->getLocalBounds().height / 2));

	m_EnemyPos = _objPos;

	m_EnemyHealth = 3;
	m_EnemySpeed = rand() % 6;

	if (m_EnemySpeed == 0)
	{
		m_EnemySpeed = 1;
	}

	UpdateEnemy();
}

Enemy::~Enemy()
{
	delete m_EnemyTexture;
	delete m_EnemySprite;
}

sf::Sprite* Enemy::GetSprite()
{
	return m_EnemySprite;
}

void Enemy::UpdateEnemy()
{
	m_EnemySprite->setPosition(m_EnemyPos);
}

void Enemy::MoveEnemy(bool _tracking, sf::Vector2f _movePos)
{
	if (_tracking)
	{
		int xDifference = _movePos.x - m_EnemyPos.x;
		int yDifference = _movePos.y - m_EnemyPos.y;

		float moveMultiplier = (abs(xDifference) + abs(yDifference)) / m_EnemySpeed;

		if (moveMultiplier != 0)
		{
			m_EnemyPos = sf::Vector2f(m_EnemyPos.x + xDifference / moveMultiplier, m_EnemyPos.y + yDifference / moveMultiplier);
		}
	}
	else
	{
		return;
	}
}