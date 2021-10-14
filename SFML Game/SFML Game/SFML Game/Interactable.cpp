#include "Interactable.h"

/*
	Function: Interact()
	Returns: bool
	Parametres: sf::Vector2f _playerPos, sf::Vector2f _interactPos
	Description: Checks if interactable can be interacted with based on distance to player,
		returns true or false accordingly
*/
bool Interactable::Interact(sf::Vector2f _playerPos, sf::Vector2f _interactPos)
{
	// Checking if player is close enough to interact with object
	int playerX = _playerPos.x;
	int playerY = _playerPos.y;

	int interactX = _interactPos.x;
	int interactY = _interactPos.y;

	int dist = sqrt(((playerX - interactX) * (playerX - interactX)) + ((playerY - interactY) * (playerY - interactY)));

	if (dist <= m_distance)
	{
		return true;
	}

	return false;
}

Interactable::Interactable()
{
	// Initialising variables 
	m_isButton = false;
	m_intSprite = new sf::Sprite;
	m_canInteract = false;
	m_interacted = false;
	m_isDoor = false;

	m_distance = 100;
}

Interactable::~Interactable()
{
	// Deallocating memory
	delete m_intSprite;
	m_intSprite = nullptr;
}
