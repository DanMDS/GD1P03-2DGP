#include <iostream>
#include "Player.h"

Player::Player(sf::String _spritePath, sf::Vector2f _objPos)
{
	m_PlayerTexture = new sf::Texture();
	if (!m_PlayerTexture->loadFromFile(_spritePath))
	{
		std::cout << "Error: " << std::string(_spritePath) << " failed to load";
	}

	m_PlayerSprite = new sf::Sprite();
	m_PlayerSprite->setTexture(*m_PlayerTexture);

	m_PlayerSprite->setOrigin(sf::Vector2f(m_PlayerSprite->getLocalBounds().width / 2, m_PlayerSprite->getLocalBounds().height / 2));

	m_PlayerPos = _objPos;

	m_PlayerHealth = 3;
	m_PlayerSpeed = 5;

	UpdatePlayer();
}

Player::~Player()
{
	delete m_PlayerTexture;
	delete m_PlayerSprite;
}

sf::Sprite* Player::GetSprite()
{
	return m_PlayerSprite;
}

void Player::UpdatePlayer()
{
	m_PlayerSprite->setPosition(m_PlayerPos);
}

sf::Vector2f Player::GetPlayerPosition()
{
	return m_PlayerPos;
}

void Player::SetPlayerPosition(sf::Vector2f _pos)
{
}

void Player::MovePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_PlayerPos.y -= m_PlayerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_PlayerPos.y += m_PlayerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_PlayerPos.x -= m_PlayerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_PlayerPos.x += m_PlayerSpeed;
	}
}