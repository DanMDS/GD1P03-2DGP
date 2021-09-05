#include "Manager.h"

bool Manager::CollisionBulletEnemy(Bullet _bullet, Enemy _enemy)
{
	if (_bullet.GetSprite()->getGlobalBounds().intersects(_enemy.GetSprite()->getGlobalBounds()))
	{
		return true;
	}
	return false;
}

void Manager::RunProgram()
{
	// Setting random seed to current time to ensure a different result each time
	srand(time(NULL));

	// Creating render window in 720p, setting style to only be able to close, not resise or maximise
	sf::RenderWindow window(sf::VideoMode(1280, 720), "deez nuts", sf::Style::Close);

	// Getting mouse position for later use
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	// Creating sample shape for testing mouse position
	sf::CircleShape cursor(10, 10);
	cursor.setFillColor(sf::Color::Blue);
	cursor.setOrigin(5, 5);

	// Setting window frame limit for reasonable and consistent speed values
	window.setFramerateLimit(60);

	// Creating player object, setting sprite and start position
	Player* player = new Player("sprites/player.png", playerDefaultPos);
	
	// Creating level object, setting start level to title screen
	Level* level = new Level("levels/level 1.png");

	// Declaring bullet for later use
	Bullet* bullet;

	// Creating example enemies
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
		mousePos = sf::Mouse::getPosition(window);
		cursor.setPosition(sf::Vector2f(mousePos));
		// Creating event for keyboard and/or mouse inputs
		sf::Event event;

		// Checking event
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Keyboard events for debugging
			if (event.type == sf::Event::KeyPressed)
			{
				// E: Run change level event to change to a random level and reset the players position
				if (event.key.code == sf::Keyboard::E)
				{
					level->ChangeLevel();
					player->SetPlayerPosition(playerDefaultPos);
					std::cout << "Level updated | ";
				}

				// R: Check if the level can be ended by running the check method
				if (event.key.code == sf::Keyboard::R)
				{
					std::cout << level->LevelEndCheck(player->GetPlayerPosition(), enemies.size());
				}
			}

			// Shooting a projectile when the mouse button is presssed
			if (event.type == sf::Event::MouseButtonPressed)
			{
				bullet = new Bullet(5, true, player->GetPlayerPosition(), sf::Vector2f(mousePos));
				bullets.push_back(bullet);
			}
		}

		// Checking for enemy to player collisions
		bool collision = false;
		for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies)
		{
			for (itBullets = bullets.begin(); itBullets != bullets.end(); ++itBullets)
			{
				if ((*itBullets)->GetSprite()->getGlobalBounds().intersects((*itEnemies)->GetSprite()->getGlobalBounds()))
				{
					Enemy* temp = *itEnemies;
					delete temp;
					temp = NULL;
					Bullet* temp2 = *itBullets;
					delete temp2;
					temp2 = NULL;
					enemies.erase(itEnemies);
					bullets.erase(itBullets);
					collision = true;
					break;
				}
			}
			if (collision)
			{
				collision = false;
				break;
			}
		}

		// Checking for enemy to bullet collisions
		for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies)
		{
			if (player->GetSprite()->getGlobalBounds().intersects((*itEnemies)->GetSprite()->getGlobalBounds()))
			{
				Enemy* temp = *itEnemies;
				delete temp;
				temp = NULL;
				enemies.erase(itEnemies);
				break;
			}
		}
		

		// Updating player and its position
		player->MovePlayer();
		player->UpdatePlayer();

		// Drawing everything
		window.clear();

		level->Draw(&window);

		for (itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies)
		{
			window.draw(*(*itEnemies)->GetSprite());

			(*itEnemies)->MoveEnemy(true, player->GetPlayerPosition());
			(*itEnemies)->UpdateEnemy();
		}

		for (itBullets = bullets.begin(); itBullets != bullets.end(); ++itBullets)
		{
			(*itBullets)->UpdateBullet();
			window.draw(*(*itBullets)->GetSprite());
		}

		window.draw(*player->GetSprite());

		window.draw(cursor);
		window.display();
	}

	// Deallocating memory
	for (std::vector<Enemy*>::iterator itEnemies = enemies.begin(); itEnemies != enemies.end(); ++itEnemies)
	{
		Enemy* temp = *itEnemies;
		delete temp;
		temp = NULL;
	}
	enemies.clear();

	for (std::vector<Bullet*>::iterator itBullets = bullets.begin(); itBullets != bullets.end(); ++itBullets)
	{
		Bullet* temp = *itBullets;
		delete temp;
		temp = NULL;
	}
	bullets.clear();

	delete level, player;
}