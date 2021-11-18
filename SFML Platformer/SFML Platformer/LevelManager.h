#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <fstream>
#include "Object.h"
#include "LevelObstacle.h"
#include "GrapplePoint.h"
#include "Player.h"
#include "Turret.h"
#include "Menu.h"

#pragma once

class LevelManager : public Object
{
private:
	int* m_levelsUnlocked;
	bool* m_timeTrialsUnlocked;
	int* m_currentLevel;
	int m_levelIndex;
	std::vector<Object*>* levelObjVec;
	std::vector<Object*>* objVec;
	std::vector<GrapplePoint*>* grappleVec;
	std::vector<Turret*>* turretVec;
	std::vector<sf::Text> textVec;
	sf::Font font;
	int fontSize;
	sf::Text jump;
	sf::Text shoot;
	sf::Text grapple;
	sf::Text turret;
	sf::Text checkpoint;
	sf::Text goal;
	sf::Text levelText;
	std::string tutorialText;
	std::string fileInput;
	std::ifstream fileIn;
	Player* player;
	sf::RenderWindow* window;
	Menu* m_menu;

	float m_timer;
	sf::Text m_timerText;

	int* m_turretShootCooldown;
	int* m_turretAlertDist;
	int* m_rocketSpeed;

	SoundManager* m_soundManager;

public:
	LevelManager(sf::RenderWindow* _window,
		std::vector<GrapplePoint*>* _grappleVec,
		std::vector<Object*>* _levelObjVec,
		std::vector<Object*>* _objVec,
		std::vector<Turret*>* _turretVec,
		int* _levelsUnlocked,
		int* _currentLevel,
		int* _turretShootCooldown,
		int* _turretAlertDist,
		int* _rocketSpeed,
		SoundManager* _soundManager,
		Menu* _menu,
		Player* _player, 
		b2World* _world, 
		const float& _scale);

	~LevelManager();

	void ChangeLevel(int _index = -1);

	sf::Text GetLevelText()						{ return levelText;		};
	sf::Text GetTextJump()						{ return jump;			};
	sf::Text GetTextShoot()						{ return shoot;			};
	sf::Text GetTextGrapple()					{ return grapple;		};
	std::vector<sf::Text> GetTutorialText()		{ return textVec;		};
	int GetIndex()								{ return m_levelIndex;	};

	void Level1();
	void Level2();
	void Level3();
	void Level4();
	void Level5();
};