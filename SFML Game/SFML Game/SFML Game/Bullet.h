#include <SFML/Graphics.hpp>

#pragma once

class Bullet
{
private:
	// Values for calculations
	sf::Vector2f m_bulletVector;
	int m_bulletDamage;
	float m_bulletSpeed;

	// Boolean for sprite changing
	bool m_isFriendly;

	// Bullet sprite
	sf::Image* m_bulletImage;
	sf::Sprite* m_bulletSprite;
	sf::Texture* m_bulletTexture;

public:
	// Methods

	//	Getters
	sf::Sprite* GetSprite() { return m_bulletSprite;	};
	bool isFriendly()		{ return m_isFriendly;		};

	// Update function for bullet
	void UpdateBullet();

	Bullet(float _speed, bool _isFriendly, sf::Vector2f _startPos, sf::Vector2f _mousePos = sf::Vector2f(0, 0));
	~Bullet();
};