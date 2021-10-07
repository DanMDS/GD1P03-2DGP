#include <iostream>
#include <iterator>
#include <vector>
#include <SFMl/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Level.h"
#include "Door.h"
#include "DebugWindow.h"
#include "Button.h"
#include "ParticleManager.h"

#pragma once

class Manager
{
private:
	int m_windowDimX = 1280;
	int m_windowDimY = 720;

	float arrowMove = 0.0;
	bool arrowForwards = false;

	int m_fireDelayPlayer = 400;

	int alpha = 0;

	int i;

	bool isTrans = false;

	sf::View* zoom;

	sf::RenderWindow* window;
	sf::RenderWindow* windowDebug;

	DebugWindow* debug;

	ParticleManager* particleManager;
	std::vector<ParticleManager*> particleManagerVec;
	std::vector<ParticleManager*>::iterator itParticleManagerVec;

	sf::Clock fadeClock;
	sf::Time fadeTimer;

	sf::Vector2f playerDefaultPos = sf::Vector2f(100, 360);

	sf::Sprite* arrow;
	sf::Image* arrowImage;
	sf::Texture* arrowTexture;

	sf::Sprite* heart;
	sf::Image* heartImage;
	sf::Texture* heartTexture;
	sf::Vector2f heartPos;
	sf::Image* heartNullImage;
	sf::Texture* heartNullTexture;

	std::vector<sf::Sprite*> hearts;

	std::vector<Enemy*> enemies;
	std::vector<Enemy*>::iterator itEnemies;
	std::vector<Enemy*>::iterator itEnemies2;

	std::vector<Bullet*> bullets;
	std::vector<Bullet*>::iterator itBullets;

	std::vector<Interactable*> interacts;
	std::vector<Interactable*>::iterator itInteracts;

public:
	bool CollisionBulletEnemy(Bullet _bullet, Enemy _enemy);
	float GetPlayerDistance(sf::Vector2f* _playerDist, sf::Vector2f* _entityDist);

	void ChangeLevel(int _index = 0);

	void RunProgram();

	Manager();
	~Manager();
};