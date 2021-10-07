#include "Interactable.h"
#include <iostream>

bool Interactable::Interact(sf::Vector2f _playerPos, sf::Vector2f _interactPos)
{
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

sf::Vector2f Interactable::GetInteractPos()
{
	return pos;
}

sf::Sprite* Interactable::GetSprite()
{
	return m_intSprite;
}

void Interactable::Update()
{
}

Interactable::Interactable()
{
	m_intSprite = new sf::Sprite;
	m_canInteract = false;
	m_interacted = false;
	m_isDoor = false;

	m_distance = 100;
}

Interactable::~Interactable()
{
	delete m_intSprite;

	m_intSprite = nullptr;
}
