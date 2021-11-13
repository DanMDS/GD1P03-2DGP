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

#pragma once

class Manager : public Object
{
private:
	Player* player;
	Goal* goal;
	Goal* checkpoint;

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

	std::ifstream m_iniIn;
	std::ofstream m_iniOut;
	int m_levelsUnlocked;
	bool m_timeTrialsUnlocked;
	bool m_levelsCompletedArr[5];
	bool m_timeTrialComplete[5];
	int m_currentLevel;

public:
	Manager();
	~Manager();

	void RunGame();
};