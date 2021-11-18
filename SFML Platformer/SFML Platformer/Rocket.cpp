#include "Rocket.h"
#include <iostream>

Rocket::Rocket(sf::Vector2f _targetPos, sf::Vector2f _startPos, Player* _player, int _speed)
{
	m_player = _player;
	startPos = _startPos;

	m_speed = _speed;

	m_power = 2.5f;

	tag = Tag::Rocket;

	m_image = new sf::Image();
	if (!m_image->loadFromFile("sprites/rocket.png"))
	{
		std::cout << "Error loading texture";
	}
	m_image->createMaskFromColor(sf::Color::White);
	m_texture->loadFromImage(*m_image);
	m_sprite->setTexture(*m_texture);
	m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2));
	m_sprite->setPosition(startPos);

	// Calculating bullet vector, only once since direction won't change
	int xDifference = int(_targetPos.x - startPos.x);
	int yDifference = int(_targetPos.y - startPos.y);

	float moveMultiplier = (abs(xDifference) + abs(yDifference)) / m_speed;

	if (moveMultiplier != 0)
	{
		m_bulletVector = sf::Vector2f(xDifference / moveMultiplier, yDifference / moveMultiplier);
	}

	m_sprite->setRotation(atan2(yDifference, xDifference) * (180.0f / b2_pi));											// Setting rotation and size
}

Rocket::~Rocket()
{
	m_player->Explode(m_sprite->getPosition(), m_power);
}

void Rocket::Update()
{
	m_sprite->setPosition(m_sprite->getPosition().x + m_bulletVector.x * m_speed, m_sprite->getPosition().y + m_bulletVector.y * m_speed);
}
