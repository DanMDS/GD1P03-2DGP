#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Player.h"
#include "LevelManager.h"
#include "ParticleManager.h"
#include "SoundManager.h"

#pragma once

class Goal : public Object
{
private:
	Player* m_player;
	LevelManager* m_levelManager;
	bool m_trans;
	bool m_checkpoint;
	bool m_isColliding;
	bool m_timeTrialActive;
	bool (*m_timeTrialComplete)[5];
	std::vector<ParticleManager*>* m_partVec;
	SoundManager* m_soundManager;

public:
	Goal(sf::Vector2f _pos, Player* _player, LevelManager* _levelManager, std::vector<ParticleManager*>* _partVec, bool (*_timeTrialComplete)[5], SoundManager* _soundManager, bool _checkpoint = false);
	~Goal();

	sf::Vector2f GetPos()				{ return m_sprite->getPosition();	};
	bool IsCheckpoint()					{ return m_checkpoint;				};
	
	void IsTimeTrialActive(bool _trial) { m_timeTrialActive = _trial;		};

	void Update();
};
