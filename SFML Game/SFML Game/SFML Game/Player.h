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
	sf::Sprite* m_PlayerSprite;
	sf::Texture* m_PlayerTexture;

	// 'Can interact' sprite
	sf::Image* m_interactImage;
	sf::Sprite* m_interactSprite;
	sf::Texture* m_interactTexture;

	// Player position
	sf::Vector2f m_PlayerPos;

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

	// Methods
	Player(sf::String _spritePath, sf::Vector2f _objPos);
	~Player();

	sf::Sprite* GetSprite();
	sf::Sprite* GetInteractSprite();
	sf::Vector2f GetPlayerPosition();

	Collider* GetCollider();

	int PlayerGetHealthMax();
	int PlayerGetHealthCurrent();
	int PlayerGetSpeed();
	void PlayerSetHealthCurrent(int _num);
	void PlayerSetHealthMax(int _num);
	void PlayerSetSpeed(int _num);
	void ResetPlayerState();

	bool IsDead();
	bool IsInv();
	void UpdateInv(sf::View* _view);
	void SetPlayerPosition(sf::Vector2f _pos);
	void UpdatePlayer(sf::View* _zoom);
	void MovePlayer();
};