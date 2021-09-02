#include <SFML/Graphics.hpp>

#pragma once

class Enemy
{
private:
	int m_EnemyHealth;										// Player health
	int m_EnemySpeed;

	sf::Sprite* m_EnemySprite;								// Player sprite
	sf::Texture* m_EnemyTexture;							// Player texture

	sf::Vector2f m_EnemyPos;								// Player position

public:
	Enemy(sf::String _spritePath, sf::Vector2f _objPos);	// Constructor
	~Enemy();												// Destructor

	sf::Sprite* GetSprite();								// Draw methods
	void UpdateEnemy();
	void MoveEnemy(bool _tracking, sf::Vector2f _movePos);
};