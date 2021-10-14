#include <SFML/Graphics.hpp>
#include "Collider.h"

#pragma once

class Player
{
private:
	// Ints for player current and max health, and speed
	int m_playerHealthCurrent;
	int m_playerHealthMax;
	int m_playerSpeed;

	// Variables for timings and invincibility 
	const float m_playerInvDuration = 2.0f;
	float m_playerInvTimer;
	bool m_isHit;
	bool m_isZooming;
	bool m_isDamaged;
	bool m_timerIsSet;
	bool m_invUp;
	bool m_dead;
	int m_alpha;

	// Player sprite
	sf::Sprite* m_playerSprite;
	sf::Texture* m_playerTexture;

	// 'Can interact' sprite
	sf::Image* m_interactImage;
	sf::Sprite* m_interactSprite;
	sf::Texture* m_interactTexture;

	// Player position
	sf::Vector2f m_playerPos;

	// Collider object
	Collider* m_playerCol;

public:
	// Boolean for hit effect
	bool m_zoomed;

	// Clock for timings
	sf::Clock clock;
	sf::Time timer;
	sf::Time shootTimer;
	sf::Time zoomTimer;

	// Constructor/destructor
	Player(sf::String _spritePath, sf::Vector2f _objPos);
	~Player();

	// Getters and setters
	sf::Sprite* GetSprite()						{ return m_playerSprite;			};
	sf::Sprite* GetInteractSprite()				{ return m_interactSprite;			};
	sf::Vector2f GetPlayerPosition()			{ return m_playerPos;				};
	Collider* GetCollider()						{ return m_playerCol;				};
	int PlayerGetHealthMax()					{ return m_playerHealthMax;			};
	int PlayerGetHealthCurrent()				{ return m_playerHealthCurrent;		};
	int PlayerGetSpeed()						{ return m_playerSpeed;				};
	bool IsDead()								{ return m_dead;					};
	bool IsInv()								{ return m_isHit;					};

	void PlayerSetHealthCurrent(int _num)		{ m_playerHealthCurrent += _num;	};
	void PlayerSetSpeed(int _num)				{ m_playerSpeed += _num;			};
	void ResetPlayerState();
	void SetPlayerPosition(sf::Vector2f _pos)	{ m_playerPos = _pos;				};

	// Methods
	void UpdateInv(sf::View* _view);
	void UpdatePlayer(sf::View* _zoom);
	void MovePlayer();
};