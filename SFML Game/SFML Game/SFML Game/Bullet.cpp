#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float _speed, bool _isFriendly, sf::Vector2f _bulletPos, sf::Vector2f _targetPos)
{
	// Loading sprite depending if enemy or not
	m_bulletImage = new sf::Image();
	m_bulletTexture = new sf::Texture();
	m_bulletSprite = new sf::Sprite();

	m_isFriendly = _isFriendly;
	if (m_isFriendly)
	{
		m_bulletImage->loadFromFile("sprites/player_bullet.png");
	}
	else
	{
		m_bulletImage->loadFromFile("sprites/enemy_bullet.png");
	}
	m_bulletImage->createMaskFromColor(sf::Color::White);

	m_bulletTexture->loadFromImage(*m_bulletImage);

	m_bulletSprite->setTexture(*m_bulletTexture);

	m_bulletSprite->setOrigin(m_bulletSprite->getGlobalBounds().width / 2, m_bulletSprite->getGlobalBounds().height / 2);

	m_bulletSprite->setPosition(_bulletPos);

	// Setting damage and speed values
	m_bulletDamage = 1;
	m_bulletSpeed = 2;

	//Calculating bullet vector, only once since direction won't change
	int xDifference = _targetPos.x - _bulletPos.x;
	int yDifference = _targetPos.y - _bulletPos.y;

	float moveMultiplier = (abs(xDifference) + abs(yDifference)) / _speed;

	if (moveMultiplier != 0)
	{
		m_bulletVector = sf::Vector2f(xDifference / moveMultiplier, yDifference / moveMultiplier);
	}
}

void Bullet::UpdateBullet()
{
	// Moving bullet
	m_bulletSprite->setPosition(m_bulletSprite->getPosition().x + m_bulletVector.x * m_bulletSpeed, m_bulletSprite->getPosition().y + m_bulletVector.y * m_bulletSpeed);
}

bool Bullet::isFriendly()
{
	return m_isFriendly;
}

Bullet::~Bullet()
{
	// Deallocating memory
	delete m_bulletImage, m_bulletTexture, m_bulletSprite;
	m_bulletImage = nullptr;
	m_bulletTexture = nullptr;
	m_bulletSprite = nullptr;
}

sf::Sprite* Bullet::GetSprite()
{
	return m_bulletSprite;
}