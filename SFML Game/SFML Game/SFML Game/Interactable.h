#include <SFML/Graphics.hpp>

#pragma once

class Interactable
{
private:
	bool m_canInteract;

protected:
	sf::Sprite* m_intSprite;
	sf::Vector2f pos;

public:
	int m_distance;
	bool m_interacted;
	bool m_isDoor;
	bool m_isButton;

	bool Interact(sf::Vector2f _playerPos, sf::Vector2f _interactPos);
	sf::Vector2f GetInteractPos();

	sf::Sprite* GetSprite();

	virtual void Update();

	Interactable();
	~Interactable();
};