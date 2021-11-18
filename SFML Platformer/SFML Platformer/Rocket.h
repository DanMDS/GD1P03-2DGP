#include "ParticleManager.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Object.h"
#include "Player.h"

#pragma once

class Rocket : public Object
{
private:
	sf::Vector2f m_bulletVector;
	sf::Vector2f startPos;
	int m_speed;
	Player* m_player;
	float m_power;

public:
	Rocket(sf::Vector2f _targetPos, sf::Vector2f _startPos, Player* _player, int _speed);
	~Rocket();

	void Update();
};