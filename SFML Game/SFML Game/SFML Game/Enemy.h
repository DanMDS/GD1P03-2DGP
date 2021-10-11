#include <SFML/Graphics.hpp>
#include "Collider.h"

#pragma once

class Enemy
{
private:
	// Values for calculations
	int m_enemyHealth;
	float m_enemySpeed;
	int m_shootTime;

	// Bool for different enemy types
	bool m_shooting;

	// Clock for timings
	sf::Clock clock;
	sf::Time timer;

	// Sprite
	sf::Sprite* m_enemySprite;
	sf::Texture* m_enemyTexture;

	// Position
	sf::Vector2f m_enemyPos;

	// Collider object
	Collider* m_enemyCol;

public:
	// Methods
	Enemy(sf::String _spritePath, sf::Vector2f _objPos, bool _shooting = false);	// Constructor
	~Enemy();

	sf::Sprite* GetSprite();
	sf::Vector2f GetEnemyPosition();

	Collider* GetCollider();

	bool m_playerCollision;
	bool m_shoot;

	void UpdateEnemy(sf::Vector2f _movePos);
	void MoveEnemy(sf::Vector2f _movePos);
};