#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <SFMl/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Level.h"
#include "Door.h"
#include "DebugWindow.h"
#include "Button.h"
#include "ParticleManager.h"
#include "Hud.h"

#pragma once

class Manager
{
private:
	// Window dimensions
	int m_windowDimX = 1280;
	int m_windowDimY = 720;

	// Int for death screen
	int m_levelsCompleted;
	int m_highScore;

	// File for high score storage
	std::ifstream fileIn;
	std::ofstream fileOut;

	// Variables for arrow movement
	float arrowMove = 0.0;
	bool arrowForwards = false;

	// Shooting values for player
	int m_fireDelayPlayer = 400;
	int m_bulletSpeedPlayer = 5;

	// Values for transition
	int alpha = 0;
	bool isTrans = false;

	// Bool for window visibility
	bool m_showDebug = false;

	// Int for heart placement
	int i;

	// Title screen buttons
	sf::RectangleShape* m_beginButton;
	sf::RectangleShape* m_endButton;

	// Game objects
	Player* player;
	Enemy* enemy;
	Bullet* bullet;
	Level* level;
	Door* door;
	Button* button;
	Hud* hud;

	// Sound objects
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

	// View and rectangle for screen transition effect
	sf::View* zoom;
	sf::RectangleShape* trans;

	// Font and text for death screen
	sf::Font* font;
	sf::Text* m_deathText;

	// Main and debug window
	sf::RenderWindow* window;
	sf::RenderWindow* windowDebug;

	// Debug object for button control
	DebugWindow* debug;

	// Particle system
	ParticleManager* particleManager;
	std::vector<ParticleManager*> particleManagerVec;
	std::vector<ParticleManager*>::iterator itParticleManagerVec;

	// Clock for timings
	sf::Clock fadeClock;
	sf::Time fadeTimer;

	// Player position vector
	sf::Vector2f playerDefaultPos = sf::Vector2f(100, 360);

	// Post-level arrow 
	sf::Sprite* arrow;
	sf::Image* arrowImage;
	sf::Texture* arrowTexture;

	// Heart hud
	sf::Sprite* heart;
	sf::Image* heartImage;
	sf::Texture* heartTexture;
	sf::Vector2f heartPos;
	sf::Image* heartNullImage;
	sf::Texture* heartNullTexture;

	std::vector<sf::Sprite*> hearts;

	// Vectors for enemies, bullets and interactables
	std::vector<Enemy*> enemies;
	std::vector<Enemy*>::iterator itEnemies;
	std::vector<Enemy*>::iterator itEnemies2;

	std::vector<Bullet*> bullets;
	std::vector<Bullet*>::iterator itBullets;

	std::vector<Interactable*> interacts;
	std::vector<Interactable*>::iterator itInteracts;

public:
	// Methods
	bool CollisionBulletEnemy(Bullet _bullet, Enemy _enemy);
	float GetPlayerDistance(sf::Vector2f* _playerDist, sf::Vector2f* _entityDist);

	void ChangeLevel(int _index = 0);

	void RunProgram();

	Manager();
	~Manager();
};