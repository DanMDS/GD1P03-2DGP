#include "Object.h"
#include "Rocket.h"
#include "Player.h"
#include "SoundManager.h"

#pragma once

class Turret : public Object
{
private:
	int* m_alertDist;
	int* m_fireRate;
	int* m_rocketSpeed;
	float m_playerDist;

	SoundManager* m_soundManager;

	std::vector<Object*>* m_objVec;

	sf::Image* m_gunImg;
	sf::Texture* m_gunTex;
	sf::Sprite* m_gunSpr;

	Player* m_player;
	sf::Vector2f m_playerPos;

public:
	Turret(Player* _player, sf::Vector2f _turretPos, std::vector<Object*>* _objVec, int* _fireRate, int* _alertDist, int* _rocketSpeed, SoundManager* _soundManager);
	~Turret();

	void Shoot();
	sf::Sprite* GetGun() { return m_gunSpr; };

	void SetFireRate(int* _rate) { m_fireRate = _rate; };
	void SetAlertDistance(int* _dist) { m_alertDist = _dist; };

	void Update();
};