#include <iostream>
#include "Player.h"

Player::Player(sf::String _spritePath, sf::Vector2f _objPos)
{
	// Initialising variables and loading sprites and textures
	m_alpha = 75;
	m_playerInvTimer = 0.0f;
	m_isHit = false;
	m_isZooming = false;
	m_isDamaged = false;
	m_invUp = false;
	m_dead = false;
	m_timerIsSet = false;
	m_zoomed = true;

	m_PlayerTexture = new sf::Texture();
	if (!m_PlayerTexture->loadFromFile(_spritePath))
	{
		std::cout << "Error: " << std::string(_spritePath) << " failed to load";
	}

	m_PlayerSprite = new sf::Sprite();
	m_PlayerSprite->setTexture(*m_PlayerTexture);

	m_PlayerSprite->setOrigin(sf::Vector2f(m_PlayerSprite->getLocalBounds().width / 2, m_PlayerSprite->getLocalBounds().height / 2));

	m_PlayerPos = _objPos;

	m_playerHealthMax = 3;
	m_playerHealthCurrent = 3;
	m_playerSpeed = 5;

	m_playerCol = new Collider(sf::Vector2f(m_PlayerSprite->getLocalBounds().width, m_PlayerSprite->getLocalBounds().height));

	m_interactImage = new sf::Image();
	if (!m_interactImage->loadFromFile("sprites/interact.png"))
	{
		std::cout << "Error: " << std::string("sprites/interact.png") << " failed to load";
	}
	m_interactImage->createMaskFromColor(sf::Color::Blue);

	m_interactTexture = new sf::Texture();
	m_interactTexture->loadFromImage(*m_interactImage);

	m_interactSprite = new sf::Sprite();

	m_interactSprite->setTexture(*m_interactTexture);

	m_interactSprite->setOrigin(sf::Vector2f(m_interactSprite->getLocalBounds().width / 2, m_interactSprite->getLocalBounds().height * 3));

	std::cout << m_playerHealthCurrent;
}

Player::~Player()
{
	// Deallocating memory
	delete m_playerCol;
	delete m_PlayerTexture;
	delete m_PlayerSprite;
	delete m_interactTexture;
	delete m_interactSprite;
}

sf::Sprite* Player::GetSprite()
{
	return m_PlayerSprite;
}

sf::Sprite* Player::GetInteractSprite()
{
	return m_interactSprite;
}

void Player::UpdatePlayer(sf::View* _zoom)
{
	// Updating player position, dead boolean, health and zoom and invincibility effects
	if (m_playerHealthCurrent <= 0)
	{
		m_dead = true;
	}
	else
	{
		m_dead = false;
	}

	m_PlayerSprite->setPosition(m_PlayerPos);
	m_interactSprite->setPosition(m_PlayerPos);

	if (m_isHit)
	{
		if (m_isZooming)
		{
			if (clock.getElapsedTime().asMilliseconds() - zoomTimer.asMilliseconds() < 1000/30)
			{
				_zoom->zoom(0.99);
			}
			else
			{
				m_timerIsSet = false;
				m_isZooming = false;
			}
		}
		else
		{
			if (!m_timerIsSet)
			{
				zoomTimer = clock.getElapsedTime();
				m_timerIsSet = true;
			}
			if (clock.getElapsedTime().asMilliseconds() - zoomTimer.asMilliseconds() < 1000/30)
			{
				_zoom->zoom(1/0.99);
			}
			else
			{
				m_zoomed = true;
			}
		}
		if (!m_isDamaged)
		{
			m_playerHealthCurrent -= 1;
			m_isDamaged = true;
			std::cout << m_playerHealthCurrent;
		}
		if (clock.getElapsedTime().asSeconds() - timer.asSeconds() < 2)
		{
			if (m_alpha > 200)
			{
				m_invUp = false;
			}
			else if (m_alpha < 50)
			{
				m_invUp = true;
			}

			if (m_invUp)
			{
				m_alpha += 15;
			}
			else
			{
				m_alpha -= 15;
			}
			m_PlayerSprite->setColor(sf::Color(255, 255, 255, m_alpha));
		}
		else
		{
			m_PlayerSprite->setColor(sf::Color(255, 255, 255, 255));
			m_isHit = false;
			m_alpha = 75;
			m_isDamaged = false;
		}
	}
}

sf::Vector2f Player::GetPlayerPosition()
{
	return m_PlayerPos;
}

Collider* Player::GetCollider()
{
	return m_playerCol;
}

int Player::PlayerGetHealthMax()
{
	return m_playerHealthMax;
}

int Player::PlayerGetHealthCurrent()
{
	return m_playerHealthCurrent;
}

int Player::PlayerGetSpeed()
{
	return m_playerSpeed;
}

void Player::PlayerSetHealthCurrent(int _num)
{
	m_playerHealthCurrent += _num;
}

void Player::PlayerSetHealthMax(int _num)
{
	m_playerHealthMax += _num;
}

void Player::PlayerSetSpeed(int _num)
{
	m_playerSpeed = _num;
}

void Player::ResetPlayerState()
{
	std::cout << "test";
	m_dead = false;
	m_playerHealthCurrent = m_playerHealthMax;
}

bool Player::IsDead()
{
	return m_dead;
}

bool Player::IsInv()
{
	return m_isHit;
}

void Player::UpdateInv(sf::View* _view)
{
	// On hit event
	m_zoomed = false;
	zoomTimer = clock.getElapsedTime();
	m_timerIsSet = false;
	m_isZooming = true;
	m_isHit = true;
	timer = clock.getElapsedTime();
}

void Player::SetPlayerPosition(sf::Vector2f _pos)
{
	m_PlayerPos = _pos;
}

void Player::MovePlayer()
{
	// Moving player depending on keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_playerCol->m_colTop)
	{
		m_PlayerPos.y -= m_playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_playerCol->m_colBottom)
	{
		m_PlayerPos.y += m_playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_playerCol->m_colLeft)
	{
		m_PlayerPos.x -= m_playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_playerCol->m_colRight)
	{
		m_PlayerPos.x += m_playerSpeed;
	}
}