#include <SFML/Graphics.hpp>
#include "Collider.h"

#pragma once

class Enemy
{
private:
	int m_enemyHealth;										// Player health
	float m_enemySpeed;
	int m_shootTime;

	bool m_shooting;

	sf::Clock clock;
	sf::Time timer;

	sf::Sprite* m_enemySprite;								// Player sprite
	sf::Texture* m_enemyTexture;							// Player texture

	sf::Vector2f m_enemyPos;								// Player position

	Collider* m_enemyCol;

public:
	Enemy(sf::String _spritePath, sf::Vector2f _objPos, bool _shooting = false);	// Constructor
	~Enemy();												// Destructor

	sf::Sprite* GetSprite();								// Draw methods
	sf::Vector2f GetEnemyPosition();

	Collider* GetCollider();

	bool m_playerCollision;
	bool m_shoot;

	void UpdateEnemy(sf::Vector2f _movePos);
	void MoveEnemy(sf::Vector2f _movePos);
};