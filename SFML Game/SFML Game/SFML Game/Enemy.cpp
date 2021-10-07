#include <iostream>
#include "Enemy.h"

Enemy::Enemy(sf::String _spritePath, sf::Vector2f _objPos, bool _shooting)
{
	m_playerCollision = false;

	m_enemyTexture = new sf::Texture();
	if (!m_enemyTexture->loadFromFile(_spritePath))
	{
		std::cout << "Error: " << std::string(_spritePath) << " failed to load";
	}

	m_enemySprite = new sf::Sprite();
	m_enemySprite->setTexture(*m_enemyTexture);

	m_enemySprite->setOrigin(sf::Vector2f(m_enemySprite->getLocalBounds().width / 2, m_enemySprite->getLocalBounds().height / 2));

	m_enemyPos = _objPos;

	m_enemySprite->setPosition(_objPos);

	m_enemyHealth = 3;
	m_enemySpeed = rand() % 4 + 2;
	m_shootTime = rand() % 500 + 500;

	timer = clock.getElapsedTime();

	m_shooting = _shooting;
	m_shoot = false;

	m_enemyCol = new Collider(sf::Vector2f(m_enemySprite->getLocalBounds().width, m_enemySprite->getLocalBounds().height));
	
}

Enemy::~Enemy()
{
	delete m_enemyTexture;
	delete m_enemySprite;
}

sf::Sprite* Enemy::GetSprite()
{
	return m_enemySprite;
}

sf::Vector2f Enemy::GetEnemyPosition()
{
	return m_enemyPos;
}

Collider* Enemy::GetCollider()
{
	return m_enemyCol;
}

void Enemy::UpdateEnemy(sf::Vector2f _movePos)
{
	if (!m_shooting)
	{
		MoveEnemy(_movePos);
		m_enemySprite->setPosition(m_enemyPos);
	}
	else if (clock.getElapsedTime().asMilliseconds() - timer.asMilliseconds() > m_shootTime)
	{
		timer = clock.getElapsedTime();
		m_shoot = true;
	}
}

void Enemy::MoveEnemy(sf::Vector2f _movePos)
{
	if (!m_playerCollision)
	{
		int xDifference = _movePos.x - m_enemyPos.x;
		int yDifference = _movePos.y - m_enemyPos.y;

		float moveMultiplier = (abs(xDifference) + abs(yDifference)) / m_enemySpeed;

		if (moveMultiplier != 0)
		{
			if (GetCollider()->m_colTop)
			{
				if (yDifference <= 0)
				{
					yDifference = 0;
				}
			}
			if (GetCollider()->m_colBottom)
			{
				if (yDifference >= 0)
				{
					yDifference = 0;
				}
			}
			if (GetCollider()->m_colLeft)
			{
				if (xDifference <= 0)
				{
					xDifference = 0;
				}
			}
			if (GetCollider()->m_colRight)
			{
				if (xDifference >= 0)
				{
					xDifference = 0;
				}
			}
			m_enemyPos = sf::Vector2f(m_enemyPos.x + xDifference / moveMultiplier, m_enemyPos.y + yDifference / moveMultiplier);
		}
	}
	else
	{
		return;
	}
}