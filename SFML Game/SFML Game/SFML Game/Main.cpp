#include <iostream>
#include <iterator>
#include <vector>
#include <SFMl/Graphics.hpp>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1280, 720), "deez nuts", sf::Style::Close);	// Creating window so that it can't be resized or maximised but can be closed

	sf::CircleShape shape(25.0f);
	shape.setFillColor(sf::Color::Blue);
	sf::Vector2f temp(40, 40);

	window.setFramerateLimit(60);

	std::vector<Enemy*> enemies;
	std::vector<Enemy*>::iterator itEnemies;

	Player player("sprites/SpriteText.png", temp);

	Enemy* enemy = new Enemy("sprites/enemy.png", sf::Vector2f(400, 400));
	enemies.push_back(enemy);

	enemy = new Enemy("sprites/enemy.png", sf::Vector2f(400, 600));
	enemies.push_back(enemy);

	enemy = new Enemy("sprites/enemy.png", sf::Vector2f(600, 400));
	enemies.push_back(enemy);

	enemy = new Enemy("sprites/enemy.png", sf::Vector2f(600, 600));
	enemies.push_back(enemy);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies)
		{
			if (player.GetSprite()->getGlobalBounds().intersects((*itEnemies)->GetSprite()->getGlobalBounds()))
			{
				Enemy* temp = *itEnemies;
				delete temp;
				temp = NULL;
				enemies.erase(itEnemies);
				break;
			}
		}

		window.clear();

		for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies)
		{
			window.draw(*(*itEnemies)->GetSprite());
			if (player.GetSprite()->getGlobalBounds().intersects((*itEnemies)->GetSprite()->getGlobalBounds()))
			{
				Enemy* temp = *itEnemies;
				delete temp;
				temp = NULL;
				enemies.erase(itEnemies);
				break;
			}

			(*itEnemies)->MoveEnemy(true, player.GetPlayerPosition());
			(*itEnemies)->UpdateEnemy();
		}

		window.draw(shape);
		player.MovePlayer();
		player.UpdatePlayer();
		window.draw(*player.GetSprite());
		window.display();
	}

	for (std::vector<Enemy*>::iterator itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies)
	{
		Enemy* temp = *itEnemies;
		delete temp;
		temp = NULL;
	}

	enemies.clear();

	return 0;
}