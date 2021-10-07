#include <SFML/Graphics.hpp>

#pragma once

class Bullet
{
private:
	sf::Vector2f m_bulletVector;
	int m_bulletDamage;
	int m_bulletSpeed;

	bool m_isFriendly;

	sf::Image m_bulletImage;
	sf::Sprite m_bulletSprite;
	sf::Texture m_bulletTexture;

public:
	sf::Sprite* GetSprite();

	void BulletEnemyMove(int _speed, sf::Vector2f _playerPos);
	void UpdateBullet();

	bool isFriendly();

	Bullet(int _speed, bool _isFriendly, sf::Vector2f _startPos, sf::Vector2f _mousePos = sf::Vector2f(0, 0));
	~Bullet();
};