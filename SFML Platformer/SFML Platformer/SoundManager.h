#include <SFML/Audio.hpp>

#pragma once

class SoundManager
{
private:
	std::vector<sf::SoundBuffer*> m_bufVec;
	std::vector<sf::Sound*> m_sndVec;

	sf::SoundBuffer* m_bufShootPlayer;
	sf::SoundBuffer* m_bufShootEnemy;
	sf::SoundBuffer* m_bufExplode;
	sf::SoundBuffer* m_bufDie;
	sf::SoundBuffer* m_bufWin;
	sf::SoundBuffer* m_bufLand;
	sf::SoundBuffer* m_bufMenu;
	sf::SoundBuffer* m_bufCheckpoint;
	sf::SoundBuffer* m_bufGrappleStart;
	sf::SoundBuffer* m_bufGrappleEnd;

	sf::Sound* m_sndShootPlayer;
	sf::Sound* m_sndShootEnemy;
	sf::Sound* m_sndExplode;
	sf::Sound* m_sndDie;
	sf::Sound* m_sndWin;
	sf::Sound* m_sndLand;
	sf::Sound* m_sndMenu;
	sf::Sound* m_sndCheckpoint;
	sf::Sound* m_sndGrappleStart;
	sf::Sound* m_sndGrappleEnd;

	sf::Music* m_music;

	int* m_soundVolume;
	int* m_musicVolume;

public:
	// Constructor/destructor
	SoundManager(int* _sound, int* _music);
	~SoundManager();

	void UpdateVolume();

	void PlaySoundShootPlayer()		{ m_sndShootPlayer->play(); };
	void PlaySoundShootEnemy()		{ m_sndShootEnemy->play();	};
	void PlaySoundExlode()			{ m_sndExplode->play();		};
	void PlaySoundDie()				{ m_sndDie->play();			};
	void PlaySoundWin()				{ m_sndWin->play();			};
	void PlaySoundLand()			{ m_sndLand->play();		};
	void PlaySoundMenu()			{ m_sndMenu->play();		};
	void PlaySoundCheckpoint()		{ m_sndCheckpoint->play();	};
	void PlaySoundGrappleStart()	{ m_sndGrappleStart->play();};
	void PlaySoundGrappleEnd()		{ m_sndGrappleEnd->play();	};
};