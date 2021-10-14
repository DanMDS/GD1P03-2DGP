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

	m_playerTexture = new sf::Texture();
	if (!m_playerTexture->loadFromFile(_spritePath))
	{
		std::cout << "Error: " << std::string(_spritePath) << " failed to load";
	}

	m_playerSprite = new sf::Sprite();
	m_playerSprite->setTexture(*m_playerTexture);

	m_playerSprite->setOrigin(sf::Vector2f(m_playerSprite->getLocalBounds().width / 2, m_playerSprite->getLocalBounds().height / 2));

	m_playerPos = _objPos;

	m_playerHealthMax = 3;
	m_playerHealthCurrent = 3;
	m_playerSpeed = 5;

	m_playerCol = new Collider(sf::Vector2f(m_playerSprite->getLocalBounds().width, m_playerSprite->getLocalBounds().height));

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
}

Player::~Player()
{
	// Deallocating memory
	delete m_playerCol;
	delete m_playerTexture;
	delete m_playerSprite;
	delete m_interactTexture;
	delete m_interactSprite;
}

/*
	Function: UpdatePlayer()
	Returns: void
	Parametres: sf::View* _zoom
	Summary: Updates all player related variables;
		Checks if player is dead, sets m_dead boolean accordingly
		Moves sprites
		Sets invincibility and zoom effect according to m_isHit boolean
*/
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

	m_playerSprite->setPosition(m_playerPos);
	m_interactSprite->setPosition(m_playerPos);

	if (m_isHit)
	{
		if (m_isZooming)
		{
			if (clock.getElapsedTime().asMilliseconds() - zoomTimer.asMilliseconds() < 1000/30)
			{
				_zoom->zoom(0.99f);
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
				_zoom->zoom(1/0.99f);
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
			m_playerSprite->setColor(sf::Color(255, 255, 255, m_alpha));
		}
		else
		{
			m_playerSprite->setColor(sf::Color(255, 255, 255, 255));
			m_isHit = false;
			m_alpha = 75;
			m_isDamaged = false;
		}
	}
}

/*
	Function: ResetPlayerState()
	Return: void
	Parametres: none
	Summary: Sets player back to not m_dead and full health
*/
void Player::ResetPlayerState()
{
	m_dead = false;
	m_playerHealthCurrent = m_playerHealthMax;
}

/*
	Function: UpdateInv()
	Returns: void
	Parametres: sf::View* _view
	Summary: Resets neccessary booleans and starts timers for invincibility and zoom effect
*/
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

/*
	Function: MovePlayer()
	Returns: void
	Parametres: none
	Summary: Moves player based on wASD input and collider variables
*/
void Player::MovePlayer()
{
	// Moving player depending on keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_playerCol->m_colTop)
	{
		m_playerPos.y -= m_playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_playerCol->m_colBottom)
	{
		m_playerPos.y += m_playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_playerCol->m_colLeft)
	{
		m_playerPos.x -= m_playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !m_playerCol->m_colRight)
	{
		m_playerPos.x += m_playerSpeed;
	}
}