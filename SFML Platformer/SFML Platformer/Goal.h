#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Player.h"
#include "LevelManager.h"
#include "ParticleManager.h"

#pragma once

class Goal : public Object
{
private:
	Player* m_player;
	LevelManager* m_levelManager;
	bool m_trans;
	bool m_checkpoint;
	bool m_isColliding;
	std::vector<ParticleManager*>* m_partVec;

public:
	Goal(sf::Vector2f _pos, Player* _player, LevelManager* _levelManager, std::vector<ParticleManager*>* _partVec, bool _checkpoint = false);
	~Goal();

	sf::Vector2f GetPos()	{ return m_sprite->getPosition();	};
	bool IsCheckpoint()		{ return m_checkpoint;				};

	void Update();
};
