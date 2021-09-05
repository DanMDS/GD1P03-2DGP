#include <iostream>
#include <iterator>
#include <vector>
#include <SFMl/Graphics.hpp>
#include <string>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Level.h"

#pragma once

class Manager
{
private:
	sf::Vector2f playerDefaultPos = sf::Vector2f(100, 360);
	
	std::vector<Enemy*> enemies;
	std::vector<Enemy*>::iterator itEnemies;

	std::vector<Bullet*> bullets;
	std::vector<Bullet*>::iterator itBullets;

public:
	bool CollisionBulletEnemy(Bullet _bullet, Enemy _enemy);
	void RunProgram();
};