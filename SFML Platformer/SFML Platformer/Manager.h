#include <fstream>
#include "Player.h"
#include "LevelObstacle.h"
#include "PlayerContactListener.h"
#include "Object.h"
#include "GrapplePoint.h"
#include "Rocket.h"
#include "ParticleManager.h"
#include "LevelManager.h"
#include "Menu.h"
#include "Goal.h"
#include "Debug.h"
#include "SoundManager.h"

#pragma once

class Manager : public Object
{
private:
	Player* player;
	Goal* goal;
	Goal* checkpoint;

	Debug* debug;

	SoundManager* m_soundManager;

	bool canJump;
	bool deleteThis;
	bool changeLevel;
	std::vector<Object*> ObjVec;
	std::vector<Object*>::iterator ObjVecIt;
	std::vector<Object*>::iterator ObjVecIt2;
	std::vector<GrapplePoint*> grappleVec;
	std::vector<Turret*> turretVec;
	std::vector<Object*> levelObjVec;

	std::vector<ParticleManager*> partVec;
	std::vector<ParticleManager*>::iterator partVecIt;

	sf::ContextSettings contSet;

	sf::Vector2f mousePos;
	sf::RenderWindow* window;
	sf::View view;

	PlayerContactListener* contactListener;

	LevelManager* levelManager;

	Menu* menu;

	int m_rocketSpeed;
	int m_turretShootCooldown;
	int m_turretAlertDist;

	std::ifstream m_iniIn;
	std::ofstream m_iniOut;
	int m_levelsUnlocked;
	bool m_timeTrialsUnlocked;
	bool m_timeTrialComplete[5];
	int m_currentLevel;

	sf::Clock clock;
	sf::Clock m_trialClock;
	sf::Time m_shootTimer;
	sf::Time m_trialTimer;
	int m_shootCooldown;
	float m_trialTime;

	sf::Font m_font;
	sf::Text m_timerText;

	std::ifstream m_soundIn;
	std::ofstream m_soundOut;
	int m_soundVolume;
	int m_musicVolume;

public:
	Manager();
	~Manager();

	void RunGame();
};