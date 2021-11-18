#include <iostream>
#include "SoundManager.h"

SoundManager::SoundManager(int* _sound, int* _music)
{
	m_soundVolume = _sound;
	m_musicVolume = _music;

	m_music = new sf::Music();
	
	if (!m_music->openFromFile("sounds/music.wav"))
	{
		std::cout << "Error loading music";
	}
	m_music->play();
	m_music->setLoop(true);

	m_bufShootPlayer = new sf::SoundBuffer();
	if (!m_bufShootPlayer->loadFromFile("sounds/player_shoot.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufShootEnemy = new sf::SoundBuffer();
	if (!m_bufShootEnemy->loadFromFile("sounds/enemy_shoot.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufExplode = new sf::SoundBuffer();
	if (!m_bufExplode->loadFromFile("sounds/explode.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufDie = new sf::SoundBuffer();
	if (!m_bufDie->loadFromFile("sounds/die.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufWin = new sf::SoundBuffer();
	if (!m_bufWin->loadFromFile("sounds/win.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufLand = new sf::SoundBuffer();
	if (!m_bufLand->loadFromFile("sounds/land.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufMenu = new sf::SoundBuffer();
	if (!m_bufMenu->loadFromFile("sounds/menu.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufCheckpoint = new sf::SoundBuffer();
	if (!m_bufCheckpoint->loadFromFile("sounds/menu.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufGrappleStart = new sf::SoundBuffer();
	if (!m_bufGrappleStart->loadFromFile("sounds/grapple_start.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufGrappleEnd = new sf::SoundBuffer();
	if (!m_bufGrappleEnd->loadFromFile("sounds/grapple_end.wav"))
	{
		std::cout << "Error loading player shoot sound";
	}

	m_bufVec.push_back(m_bufShootPlayer);
	m_bufVec.push_back(m_bufShootEnemy);
	m_bufVec.push_back(m_bufExplode);
	m_bufVec.push_back(m_bufDie);
	m_bufVec.push_back(m_bufWin);
	m_bufVec.push_back(m_bufLand);
	m_bufVec.push_back(m_bufMenu);
	m_bufVec.push_back(m_bufCheckpoint);
	m_bufVec.push_back(m_bufGrappleStart);
	m_bufVec.push_back(m_bufGrappleEnd);


	m_sndShootPlayer = new sf::Sound();
	m_sndShootEnemy = new sf::Sound();
	m_sndExplode = new sf::Sound();
	m_sndDie = new sf::Sound();
	m_sndWin = new sf::Sound();
	m_sndLand = new sf::Sound();
	m_sndMenu = new sf::Sound();
	m_sndCheckpoint = new sf::Sound();
	m_sndGrappleStart = new sf::Sound();
	m_sndGrappleEnd = new sf::Sound();

	m_sndShootPlayer->setBuffer(*m_bufShootPlayer);
	m_sndShootEnemy->setBuffer(*m_bufShootEnemy);
	m_sndExplode->setBuffer(*m_bufExplode);
	m_sndDie->setBuffer(*m_bufDie);
	m_sndWin->setBuffer(*m_bufWin);
	m_sndLand->setBuffer(*m_bufLand);
	m_sndMenu->setBuffer(*m_bufMenu);
	m_sndCheckpoint->setBuffer(*m_bufCheckpoint);
	m_sndGrappleStart->setBuffer(*m_bufGrappleStart);
	m_sndGrappleEnd->setBuffer(*m_bufGrappleEnd);

	m_sndVec.push_back(m_sndShootPlayer);
	m_sndVec.push_back(m_sndShootEnemy);
	m_sndVec.push_back(m_sndExplode);
	m_sndVec.push_back(m_sndDie);
	m_sndVec.push_back(m_sndWin);
	m_sndVec.push_back(m_sndLand);
	m_sndVec.push_back(m_sndMenu);
	m_sndVec.push_back(m_sndCheckpoint);
	m_sndVec.push_back(m_sndGrappleStart);
	m_sndVec.push_back(m_sndGrappleEnd);

	UpdateVolume();
}

SoundManager::~SoundManager()
{
	m_music->stop();

	delete m_music;
	m_music = nullptr;

	for (auto& itr : m_bufVec)
	{
		delete itr;
		itr = nullptr;
	}
	for (auto& itr : m_sndVec)
	{
		delete itr;
		itr = nullptr;
	}

	m_bufVec.clear();
	m_sndVec.clear();
}

void SoundManager::UpdateVolume()
{
	m_music->setVolume(*m_musicVolume);

	for (auto& itr : m_sndVec)
	{
		itr->setVolume(*m_soundVolume);
	}
}