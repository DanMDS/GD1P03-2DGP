#include <iostream>
#include "Door.h"

void Door::Update(bool _levelEnd, sf::Vector2f _playerPos, Player* _player, std::vector<Enemy*> _enemies)
{
	// Updating sprites and interacted boolean
	if (_levelEnd)
	{
		m_intSprite->setTexture(*m_doorOpenTexture);
		m_locked = false;
	}
	else
	{
		m_intSprite->setTexture(*m_doorClosedTexture);
		m_locked = true;
	}

	if (m_interacted && _levelEnd)
	{
		std::cout << "test";
		m_interacted = false;
		DoorLock();
	}
}

void Door::DoorLock()
{
	// Locking door
	m_intSprite->setTexture(*m_doorClosedTexture);

	m_locked = true;
}

bool Door::DoorIsOpen()
{
	return !m_locked;
}

sf::Sprite* Door::GetSprite()
{
	return m_intSprite;
}

sf::Vector2f Door::GetDoorPosition()
{
	return m_intSprite->getPosition();
}

Door::Door(sf::Vector2f _levelDim)
{
	// Initialising variables and loading sprites and textures
	m_locked = true;
	m_isDoor = true;
	m_isButton = false;

	m_doorClosedTexture = new sf::Texture();
	m_doorOpenTexture = new sf::Texture();
	m_intSprite = new sf::Sprite();

	if (!m_doorClosedTexture->loadFromFile("sprites/door_closed.png"))
	{
		std::cout << "Error: loading door closed image \n";
	}
	if (!m_doorOpenTexture->loadFromFile("sprites/door_open.png"))
	{
		std::cout << "Error: loading door open image \n";
	}

	m_intSprite->setTexture(*m_doorClosedTexture);

	m_intSprite->setOrigin(m_intSprite->getGlobalBounds().width / 2, m_intSprite->getGlobalBounds().height / 2);

	pos = sf::Vector2f(_levelDim.x - m_intSprite->getGlobalBounds().width / 2, _levelDim.y / 2);
	m_intSprite->setPosition(pos);
}

Door::~Door()
{
	// Deallocating memory
	delete m_doorClosedTexture;
	delete m_doorOpenTexture;

	m_doorClosedTexture = nullptr;
	m_doorOpenTexture = nullptr;
}
