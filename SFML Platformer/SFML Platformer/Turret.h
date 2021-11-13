#include "Object.h"
#include "Rocket.h"
#include "Player.h"

#pragma once

class Turret : public Object
{
private:
	float m_alertDist;
	float m_fireRate;
	float m_playerDist;

	std::vector<Object*>* m_objVec;

	sf::Image* m_gunImg;
	sf::Texture* m_gunTex;
	sf::Sprite* m_gunSpr;

	Player* m_player;
	sf::Vector2f m_playerPos;

public:
	Turret(Player* _player, sf::Vector2f _turretPos, std::vector<Object*>* _objVec, float _fireRate, float _alertDist);
	~Turret();

	void Shoot();
	sf::Sprite* GetGun() { return m_gunSpr; };

	void Update();
};