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

	// Bools for calculations
	bool m_playerCollision;
	bool m_shoot;

public:
	// Methods

	// Getters and setters
	void SetPlayerCollision(bool _playerCol)	{ m_playerCollision = _playerCol;	};
	void SetEnemyShoot(bool _enemyShoot)		{ m_shoot = _enemyShoot;			};

	sf::Sprite* GetSprite()						{ return m_enemySprite;				};
	sf::Vector2f GetEnemyPosition()				{ return m_enemyPos;				};
	Collider* GetCollider()						{ return m_enemyCol;				};
	bool GetPlayerCollision()					{ return m_playerCollision;			};
	bool GetEnemyShoot()						{ return m_shoot;					};

	// Update/move functions
	void UpdateEnemy(sf::Vector2f _movePos);
	void MoveEnemy(sf::Vector2f _movePos);

	// Constructor/destructor
	Enemy(sf::String _spritePath, sf::Vector2f _objPos, bool _shooting = false);
	~Enemy();
};