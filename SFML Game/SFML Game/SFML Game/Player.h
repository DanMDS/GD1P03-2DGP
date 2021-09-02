#include <SFML/Graphics.hpp>

#pragma once

class Player
{
private:
	int m_PlayerHealth;										// Player health
	int m_PlayerSpeed;

	sf::Sprite* m_PlayerSprite;								// Player sprite
	sf::Texture* m_PlayerTexture;							// Player texture

	sf::Vector2f m_PlayerPos;								// Player position

public:
	Player(sf::String _spritePath, sf::Vector2f _objPos);	// Constructor
	~Player();												// Destructor

	sf::Sprite* GetSprite();								// Draw methods
	sf::Vector2f GetPlayerPosition();
	void UpdatePlayer();
	void MovePlayer();
};