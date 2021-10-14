#include <SFML/Audio.hpp>

#pragma once

class SoundManager
{
private:
	// Sound objects
	std::vector<sf::SoundBuffer*> soundBufferVec;
	std::vector<sf::Sound*> soundVec;

	sf::SoundBuffer* m_bufferHitEnemy;
	sf::SoundBuffer* m_bufferHitPlayer;
	sf::SoundBuffer* m_bufferHitWall;
	sf::SoundBuffer* m_bufferButton;
	sf::SoundBuffer* m_bufferDoor;
	sf::SoundBuffer* m_bufferShootPlayer;
	sf::SoundBuffer* m_bufferShootEnemy;
	sf::SoundBuffer* m_bufferLose;

	sf::Sound* m_soundHitEnemy;
	sf::Sound* m_soundHitPlayer;
	sf::Sound* m_soundHitWall;
	sf::Sound* m_soundButton;
	sf::Sound* m_soundDoor;
	sf::Sound* m_soundShootPlayer;
	sf::Sound* m_soundShootEnemy;
	sf::Sound* m_soundLose;

	sf::Music* m_music;

public:
	// Constructor/destructor
	SoundManager();
	~SoundManager();

	// Methods for playing/stoppings sounds and changing music volume for mute button
	void PlaySoundHitEnemy()		{ m_soundHitEnemy->play();		};
	void PlaySoundHitPlayer()		{ m_soundHitPlayer->play();		};
	void PlaySoundHitWall()			{ m_soundHitWall->play();		};
	void PlaySoundButton()			{ m_soundButton->play();		};
	void PlaySoundDoor()			{ m_soundDoor->play();			};
	void PlaySoundShootPlayer()		{ m_soundShootPlayer->play();	};
	void PlaySoundShootEnemy()		{ m_soundShootEnemy->play();	};
	void PlaySoundLose()			{ m_soundLose->play();			};
	void PlayMusic()				{ m_music->play();				};
	void SetMusicVolume(float _vol) { m_music->setVolume(_vol);		};

	// Other methods
	void StopSounds();
};