#include <SFML/Graphics.hpp>
#include "Collider.h"

#pragma once

class Player
{
private:
	int m_playerHealthCurrent;								// Player health
	int m_playerHealthMax;
	int m_playerSpeed;

	const float m_playerInvDuration = 2.0f;					// Variables for player i-frames
	float m_playerInvTimer;
	bool m_isHit;
	bool m_isZoomed;
	bool m_isDamaged;
	bool m_invUp;
	bool m_dead;
	int m_alpha;
	float m_zoomAmount;

	sf::Sprite* m_PlayerSprite;								// Player sprite
	sf::Texture* m_PlayerTexture;							// Player texture

	sf::Image* m_interactImage;								// Interact image
	sf::Sprite* m_interactSprite;							// Interact sprite
	sf::Texture* m_interactTexture;							// Interact texture

	sf::Vector2f m_PlayerPos;								// Player position

	Collider* m_playerCol;

public:
	Player(sf::String _spritePath, sf::Vector2f _objPos);	// Constructor
	~Player();												// Destructor

	sf::Sprite* GetSprite();								// Draw methods
	sf::Sprite* GetInteractSprite();
	sf::Vector2f GetPlayerPosition();

	sf::Clock clock;										// Timer for cooldowns/i-frames
	sf::Time timer;
	sf::Time shootTimer;

	Collider* GetCollider();

	int PlayerGetHealthMax();
	int PlayerGetHealthCurrent();
	void PlayerSetHealthCurrent(int _num);
	void PlayerSetHealthMax(int _num);
	void ResetPlayerState();

	bool IsDead();
	bool IsInv();
	void UpdateInv(sf::View* _view);
	void SetPlayerPosition(sf::Vector2f _pos);
	void UpdatePlayer(sf::View* _zoom);
	void MovePlayer();
};