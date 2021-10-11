#include <SFML/Graphics.hpp>

#pragma once

class Interactable
{
private:
	// Bool for checkign whether to run interact script
	bool m_canInteract;

protected:
	// Sprite 
	sf::Sprite* m_intSprite;

	// Position
	sf::Vector2f pos;

public:
	// Values and bools for easy calculations
	int m_distance;
	bool m_interacted;
	bool m_isDoor;
	bool m_isButton;

	// Methods
	bool Interact(sf::Vector2f _playerPos, sf::Vector2f _interactPos);
	sf::Vector2f GetInteractPos();

	sf::Sprite* GetSprite();

	virtual void Update();

	Interactable();
	~Interactable();
};