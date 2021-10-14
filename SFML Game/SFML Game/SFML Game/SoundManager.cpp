#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	// Creating sound objects
	m_bufferHitEnemy = new sf::SoundBuffer();
	if (!m_bufferHitEnemy->loadFromFile("sounds/hit_enemy.wav"))
	{
		std::cout << "Error: loading sound 'hit enemy'";
	}
	soundBufferVec.push_back(m_bufferHitEnemy);
	m_soundHitEnemy = new sf::Sound();
	m_soundHitEnemy->setBuffer(*m_bufferHitEnemy);
	m_soundHitEnemy->setVolume(50.0f);
	soundVec.push_back(m_soundHitEnemy);

	m_bufferHitPlayer = new sf::SoundBuffer();
	if (!m_bufferHitPlayer->loadFromFile("sounds/hit_player.wav"))
	{
		std::cout << "Error: loading sound 'hit player'";
	}
	soundBufferVec.push_back(m_bufferHitPlayer);
	m_soundHitPlayer = new sf::Sound();
	m_soundHitPlayer->setBuffer(*m_bufferHitPlayer);
	m_soundHitPlayer->setVolume(50.0f);
	soundVec.push_back(m_soundHitPlayer);

	m_bufferHitWall = new sf::SoundBuffer();
	if (!m_bufferHitWall->loadFromFile("sounds/hit_wall.wav"))
	{
		std::cout << "Error: loading sound 'hit player'";
	}
	soundBufferVec.push_back(m_bufferHitWall);
	m_soundHitWall = new sf::Sound();
	m_soundHitWall->setBuffer(*m_bufferHitWall);
	m_soundHitWall->setVolume(25.0f);
	soundVec.push_back(m_soundHitWall);

	m_bufferButton = new sf::SoundBuffer();
	if (!m_bufferButton->loadFromFile("sounds/button.wav"))
	{
		std::cout << "Error: loading sound 'hit player'";
	}
	soundBufferVec.push_back(m_bufferButton);
	m_soundButton = new sf::Sound();
	m_soundButton->setBuffer(*m_bufferButton);
	soundVec.push_back(m_soundButton);

	m_bufferDoor = new sf::SoundBuffer();
	if (!m_bufferDoor->loadFromFile("sounds/transition.wav"))
	{
		std::cout << "Error: loading sound 'hit player'";
	}
	soundBufferVec.push_back(m_bufferDoor);
	m_soundDoor = new sf::Sound();
	m_soundDoor->setBuffer(*m_bufferDoor);
	soundVec.push_back(m_soundDoor);

	m_bufferShootPlayer = new sf::SoundBuffer();
	if (!m_bufferShootPlayer->loadFromFile("sounds/shoot_player.wav"))
	{
		std::cout << "Error: loading sound 'hit player'";
	}
	soundBufferVec.push_back(m_bufferShootPlayer);
	m_soundShootPlayer = new sf::Sound();
	m_soundShootPlayer->setBuffer(*m_bufferShootPlayer);
	soundVec.push_back(m_soundShootPlayer);

	m_bufferShootEnemy = new sf::SoundBuffer();
	if (!m_bufferShootEnemy->loadFromFile("sounds/shoot_enemy.wav"))
	{
		std::cout << "Error: loading sound 'hit player'";
	}
	soundBufferVec.push_back(m_bufferShootEnemy);
	m_soundShootEnemy = new sf::Sound();
	m_soundShootEnemy->setBuffer(*m_bufferShootEnemy);
	m_soundShootEnemy->setVolume(50.0f);
	soundVec.push_back(m_soundShootEnemy);

	m_bufferLose = new sf::SoundBuffer();
	if (!m_bufferLose->loadFromFile("sounds/lose.wav"))
	{
		std::cout << "Error: loading sound 'hit player'";
	}
	soundBufferVec.push_back(m_bufferLose);
	m_soundLose = new sf::Sound();
	m_soundLose->setBuffer(*m_bufferLose);
	soundVec.push_back(m_soundLose);

	m_music = new sf::Music();
	m_music->openFromFile("sounds/music.wav");
	m_music->play();
	m_music->setVolume(10);
	m_music->setLoop(true);
}

SoundManager::~SoundManager()
{
	// Deallocating memory and stopping sounds
	for (auto& itr : soundVec)
	{
		delete itr;
		itr = nullptr;
	}
	soundVec.clear();

	for (auto& itr : soundBufferVec)
	{
		delete itr;
		itr = nullptr;
	}
	soundBufferVec.clear();

	delete m_music;
	m_music = nullptr;
}

/*
	Function: StopSounds()
	Returns: void
	Parametres: none
	Summary: Stops all sounds in case they are playing so that the sound thread that SFML uses can close 
		properly
*/
void SoundManager::StopSounds()
{
	for (auto& itr : soundVec)
	{
		itr->stop();
	}

	m_music->stop();
}