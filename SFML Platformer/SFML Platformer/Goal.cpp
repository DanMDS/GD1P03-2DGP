#include "Goal.h"

Goal::Goal(sf::Vector2f _pos, Player* _player, LevelManager* _levelManager, std::vector<ParticleManager*>* _partVec, bool(*_timeTrialComplete)[5], SoundManager* _soundManager, bool _checkpoint)
{
	m_player = _player;
	m_checkpoint = _checkpoint;
	m_partVec = _partVec;

	m_timeTrialComplete = _timeTrialComplete;
	m_timeTrialActive = false;

	m_soundManager = _soundManager;

	m_trans = false;
	m_isColliding = false;

	m_levelManager = _levelManager;

	tag = Tag::Goal;

	m_image = new sf::Image();

	if (!m_image->loadFromFile(_checkpoint ? "sprites/checkpoint.png" : "sprites/goal.png"))
	{
		printf("Error loading flag sprite");
	}
	m_texture->loadFromImage(*m_image);
	m_sprite->setTexture(*m_texture);
	m_sprite->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height);
	m_sprite->setPosition(_pos);
}

Goal::~Goal()
{
}

void Goal::Update()
{
	if (m_sprite->getGlobalBounds().intersects(m_player->GetSprite()->getGlobalBounds()) && !m_player->IsDead() && !m_trans)
	{
		if (!m_checkpoint && !m_isColliding)
		{
			m_player->Transition(false);
			m_trans = true;
			m_isColliding = true;

			if (m_timeTrialActive)
			{
				std::cout << "Completed time trial " << m_levelManager->GetIndex() << "\n";
				(*m_timeTrialComplete)[m_levelManager->GetIndex() - 1] = true;
			}
		}
		else if (!m_timeTrialActive)
		{
			m_player->SetStartPos(b2Vec2(m_sprite->getPosition().x, m_sprite->getPosition().y - 50), true);
			if (!m_isColliding)
			{
				m_soundManager->PlaySoundCheckpoint();
				m_partVec->push_back(new ParticleManager(sf::Color(255, 127, 0), m_sprite->getPosition(), 10));
			}
			m_isColliding = true;
		}
	}
	else
	{
		m_isColliding = false;
	}
	if (m_trans && m_player->isTransDone())
	{
		printf("change level");
		m_trans = false;
		m_levelManager->ChangeLevel(-1);
	}
}
