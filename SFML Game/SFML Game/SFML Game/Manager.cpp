#include "Manager.h"
#include <iostream>

// Declaring level object
Level* level = nullptr;

// Declaring player object
Player* player = nullptr;

// Declaring door object
Door* door = nullptr;

// Declaring bullet object
Bullet* bullet = nullptr;

// Declaring enemy object
Enemy* enemy = nullptr;

// Declaring rectangle and colour for screen transition
sf::RectangleShape trans(sf::Vector2f(1280, 720));

bool Manager::CollisionBulletEnemy(Bullet _bullet, Enemy _enemy)
{
	if (_bullet.GetSprite()->getGlobalBounds().intersects(_enemy.GetSprite()->getGlobalBounds()))
	{
		return true;
	}
	return false;
}

float Manager::GetPlayerDistance(sf::Vector2f* _playerPos, sf::Vector2f* _entityPos)
{
	int xDifference = _playerPos->x - _entityPos->x;
	int yDifference = _playerPos->y - _entityPos->y;

	return sqrt(abs(xDifference) ^ 2 + abs(yDifference) ^ 2);
}

void Manager::ChangeLevel(int _index)
{
	for (auto& itr : enemies)
	{
		Enemy* temp = itr;
		delete temp;
		temp = nullptr;
	}
	enemies.clear();

	for (auto& itr : bullets)
	{
		Bullet* temp = itr;
		delete temp;
		temp = nullptr;
	}
	bullets.clear();

	level->ChangeLevel(player, enemies, _index);

	while (interacts.size() != 1)
	{
		for (itInteracts = interacts.begin(); itInteracts != interacts.end(); itInteracts++)
		{
			if (!(*itInteracts)->m_isDoor)
			{
				delete* itInteracts;
				*itInteracts = nullptr;
				interacts.erase(itInteracts);
				break;
			}
		}
	}

	Enemy* enemy = nullptr;
	Button* button = nullptr;

	switch (level->levelIndex)
	{
	case -3:
		// Start screen

		break;
	case -2:
		// Tutorial screen

		break;
	case -1:
		// Death screen
		button = new Button(sf::Vector2f(650, 500));
		interacts.push_back(button);

		break;

		// Levels
	case 0:
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(250, 100));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(250, 150));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(300, 100));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(300, 150));
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(250, 650));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(250, 600));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(300, 650));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(300, 600));
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 300));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 360));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 420));
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(200, 100), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(200, 550), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(200, 600), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(200, 650), true);
		enemies.push_back(enemy);

		button = new Button(sf::Vector2f(100, 100));
		interacts.push_back(button);

		break;
	case 1:
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 240), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 300), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 420), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1000, 480), true);
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 240));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 300));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 360));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 420));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 480));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 240));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 300));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 360));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 420));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 480));
		enemies.push_back(enemy);

		break;
	case 2:
		button = new Button(sf::Vector2f(500, 500));
		interacts.push_back(button);

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	}
}

void CollisionEnemies(Enemy* _enemy1, Enemy* _enemy2)
{
	Collider* _col1 = _enemy1->GetCollider();
	Collider* _col2 = _enemy2->GetCollider();

	if (_col1->colBoundsBottom->getGlobalBounds().intersects(_col2->colBoundsTop->getGlobalBounds()))
	{
		_col1->m_colBottom = _col2->m_colTop = true;
	}

	if (_col1->colBoundsTop->getGlobalBounds().intersects(_col2->colBoundsBottom->getGlobalBounds()))
	{
		_col1->m_colTop = _col2->m_colBottom = true;
	}

	if (_col1->colBoundsLeft->getGlobalBounds().intersects(_col2->colBoundsRight->getGlobalBounds()))
	{
		_col1->m_colLeft = _col2->m_colRight = true;
	}

	if (_col1->colBoundsRight->getGlobalBounds().intersects(_col2->colBoundsLeft->getGlobalBounds()))
	{
		_col1->m_colRight = _col2->m_colLeft = true;
	}
}

void CollisionWall(Player* _collider, Level* _level)
{
	_collider->GetCollider()->m_colBottom = _collider->GetCollider()->m_colTop = _collider->GetCollider()->m_colLeft = _collider->GetCollider()->m_colRight = false;

	for (auto& itr : _level->GetCollider()->boundsVec)
	{
		if (_collider->GetCollider()->colBoundsTop->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colTop = true;
		}

		if (_collider->GetCollider()->colBoundsBottom->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colBottom = true;
		}

		if (_collider->GetCollider()->colBoundsLeft->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colLeft = true;
		}

		if (_collider->GetCollider()->colBoundsRight->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colRight = true;
		}
	}
}

void CollisionWall(Enemy* _collider, Level* _level)
{
	_collider->GetCollider()->m_colBottom = _collider->GetCollider()->m_colTop = _collider->GetCollider()->m_colLeft = _collider->GetCollider()->m_colRight = false;

	for (auto& itr : _level->GetCollider()->boundsVec)
	{
		if (_collider->GetCollider()->colBoundsTop->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colTop = true;
		}

		if (_collider->GetCollider()->colBoundsBottom->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colBottom = true;
		}

		if (_collider->GetCollider()->colBoundsLeft->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colLeft = true;
		}

		if (_collider->GetCollider()->colBoundsRight->getGlobalBounds().intersects(itr->getGlobalBounds()))
		{
			_collider->GetCollider()->m_colRight = true;
		}
	}
}

void CollisionPlayerEnemy(Player* _player, Enemy* _enemy)
{
	Collider* _col1 = _player->GetCollider();
	Collider* _col2 = _enemy->GetCollider();

	if (_col1->colBoundsBottom->getGlobalBounds().intersects(_col2->colBoundsTop->getGlobalBounds()))
	{
		_col1->m_colBottom = _col2->m_colTop = true;
	}

	if (_col1->colBoundsTop->getGlobalBounds().intersects(_col2->colBoundsBottom->getGlobalBounds()))
	{
		_col1->m_colTop = _col2->m_colBottom = true;
	}

	if (_col1->colBoundsLeft->getGlobalBounds().intersects(_col2->colBoundsRight->getGlobalBounds()))
	{
		_col1->m_colLeft = _col2->m_colRight = true;
	}

	if (_col1->colBoundsRight->getGlobalBounds().intersects(_col2->colBoundsLeft->getGlobalBounds()))
	{
		_col1->m_colRight = _col2->m_colLeft = true;
	}
}

void Manager::RunProgram()
{
	// Setting random seed to current time to ensure a different result each time
	srand(static_cast<unsigned int>(time(NULL)));
	
	// Getting mouse position for later use
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	// Creating sample shape for testing mouse position
	sf::CircleShape cursor(10, 10);
	cursor.setFillColor(sf::Color::Blue);
	cursor.setOrigin(5, 5);

	// Creating player object, setting sprite and start position
	player = new Player("sprites/player.png", playerDefaultPos);
	
	// Creating level object, setting start level to title screen
	level = new Level("levels/level_main.png");

	// Creating door object
	door = new Door(sf::Vector2f(m_windowDimX, m_windowDimY));
	interacts.push_back(door);

	// Setting colour of trans
	trans.setFillColor(sf::Color(0, 0, 0, 0));

	player->timer = player->clock.getElapsedTime();

	while (window->isOpen() && windowDebug->isOpen())
	{
		if (isTrans)
		{
			if (fadeClock.getElapsedTime().asMilliseconds() > 1 && alpha != 255)
			{
				trans.setFillColor(sf::Color(0, 0, 0, alpha));
				alpha = (alpha + 20 > 255) ? 255 : alpha + 20;
				fadeClock.restart();
			}
			else
			{
				isTrans = false;
			}
		}
		if (!isTrans && fadeClock.getElapsedTime().asMilliseconds() > 1 && alpha != 0)
		{
			trans.setFillColor(sf::Color(0, 0, 0, alpha));
			alpha = (alpha - 20 < 0) ? 0 : alpha - 20;
			fadeClock.restart();
		}

		mousePos = sf::Mouse::getPosition(*window);
		cursor.setPosition(sf::Vector2f(mousePos));
		// Creating events for keyboard and mouse inputs
		sf::Event event;
		sf::Event eventDebug;

		// Checking main window event
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			// Keyboard events for debugging and gameplay
			if (event.type == sf::Event::KeyPressed)
			{
				// E: Checking on interactables
				if (event.key.code == sf::Keyboard::E)
				{
					for (auto& itr : interacts)
					{
						if (itr->Interact(player->GetPlayerPosition(), itr->GetInteractPos()) && itr->m_interacted == false)
						{
							if (itr->m_isDoor && level->levelIndex != -3 && level->LevelEndCheck(enemies.size(), interacts))
							{
								isTrans = true;
							}
							else if (level->levelIndex == -1)
							{
								player->ResetPlayerState();
								itr->m_interacted = true;
								isTrans = true;
							}
							else
							{
								itr->m_interacted = true;
							}
						}
					}
				}
				// T: Run change level event to change to a random level and reset the players position
				if (event.key.code == sf::Keyboard::T)
				{
					ChangeLevel();
				}

				// R: Check if the level can be ended by running the check method
				if (event.key.code == sf::Keyboard::R)
				{
					std::cout << level->LevelEndCheck(enemies.size(), interacts);
				}
			}
		}

		if (alpha == 255 && !player->IsDead())
		{
			if (level->levelIndex == -1)
			{
				std::cout << "test";
				ChangeLevel(-3);
			}
			else
			{
				ChangeLevel();
			}
		}

		// Death event
		if (player->IsDead() && level->levelIndex != -1)
		{
			isTrans = true;
			if (alpha == 255)
			{
				ChangeLevel(-1);
			}
		}

		if (level->levelIndex == -1 && alpha == 255 && level->LevelEndCheck(enemies.size(), interacts))
		{
			ChangeLevel(-3);
		}
		// Shooting, limited to once every 500 milliseconds (default, will change with pickups)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (player->clock.getElapsedTime().asMilliseconds() - player->shootTimer.asMilliseconds() > m_fireDelayPlayer)
			{
				player->shootTimer = player->clock.getElapsedTime();
				bullet = new Bullet(5, true, player->GetPlayerPosition(), sf::Vector2f(mousePos));
				bullets.push_back(bullet);
			}
		}

		// Enemy shooting
		for (auto& itr : enemies)
		{
			if (itr->m_shoot)
			{
				bullet = new Bullet(5, false, itr->GetEnemyPosition(), player->GetPlayerPosition());
				bullets.push_back(bullet);
				itr->m_shoot = false;
			}
		}

		// Checking for enemy, player, wall and bullet collisions, not using auto iterators so that i can use vector.erase()
		std::vector<sf::RectangleShape*>::iterator itBoundsVec;
		for (itBoundsVec = level->GetCollider()->boundsVec.begin(); itBoundsVec != level->GetCollider()->boundsVec.end(); itBoundsVec++)
		{
			for (itBullets = bullets.begin(); itBullets != bullets.end(); itBullets++)
			{
				if ((*itBullets)->GetSprite()->getGlobalBounds().intersects((*itBoundsVec)->getGlobalBounds()))
				{
					if ((*itBullets)->isFriendly())
					{
						particleManager = new ParticleManager(sf::Color(200, 191, 231), (*itBullets)->GetSprite()->getPosition());
						particleManagerVec.push_back(particleManager);
					}
					else
					{
						particleManager = new ParticleManager(sf::Color::Red, (*itBullets)->GetSprite()->getPosition());
						particleManagerVec.push_back(particleManager);
					}
					Bullet* temp = *itBullets;
					delete temp;
					temp = nullptr;
					bullets.erase(itBullets);
					break;
				}
			}
		}

		for (itBullets = bullets.begin(); itBullets != bullets.end(); ++itBullets)
		{
			if (!(*itBullets)->isFriendly() && player->GetSprite()->getGlobalBounds().intersects((*itBullets)->GetSprite()->getGlobalBounds()))
			{
				particleManager = new ParticleManager(sf::Color::Red, (*itBullets)->GetSprite()->getPosition());
				particleManagerVec.push_back(particleManager);
				if (!player->IsInv())
				{
					player->UpdateInv(zoom);
				}
				delete *itBullets;
				*itBullets = nullptr;
				bullets.erase(itBullets);
				break;
			}
		}

		bool collision = false;
		for (itEnemies = enemies.begin(); itEnemies != enemies.end(); itEnemies++)
		{
			for (itBullets = bullets.begin(); itBullets != bullets.end(); ++itBullets)
			{
				if ((*itBullets)->GetSprite()->getGlobalBounds().intersects((*itEnemies)->GetSprite()->getGlobalBounds()) && (*itBullets)->isFriendly())
				{
					particleManager = new ParticleManager(sf::Color(200, 191, 231), (*itBullets)->GetSprite()->getPosition());
					particleManagerVec.push_back(particleManager);
					Enemy* temp = *itEnemies;
					delete temp;
					temp = nullptr;
					Bullet* temp2 = *itBullets;
					delete temp2;
					temp2 = nullptr;
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
			CollisionWall(*itEnemies, level);
			if (player->GetSprite()->getGlobalBounds().intersects((*itEnemies)->GetSprite()->getGlobalBounds()))
			{
				if (player->IsInv())
				{
					(*itEnemies)->m_playerCollision = true;
				}
				else
				{
					player->UpdateInv(zoom);
					Enemy* temp = *itEnemies;
					delete temp;
					temp = NULL;
					enemies.erase(itEnemies);
					break;
				}
			}
			else
			{
				(*itEnemies)->m_playerCollision = false;
			}

			for (itEnemies2 = enemies.begin(); itEnemies2 != enemies.end(); itEnemies2++)
			{
				if (itEnemies == itEnemies2)
				{
					continue;
				}
				else
				{
					CollisionEnemies(*itEnemies, *itEnemies2);
				}
			}
		}

		// Checking for player to wall collisions
		CollisionWall(player, level);
		
		// Checking debug window event
		while (windowDebug->pollEvent(eventDebug))
		{
			if (eventDebug.type == sf::Event::Closed)
			{
				windowDebug->close();
			}

			if (eventDebug.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					debug->CheckButtons(windowDebug, sf::Vector2f(mousePos));
				}
			}
		}

		// Updating objects where needed
		if (!isTrans && level->levelIndex != -1)
		{
			door->Update(level->LevelEndCheck(enemies.size(), interacts), player->GetPlayerPosition(), player, enemies);
		}

		player->MovePlayer();
		player->UpdatePlayer(zoom);
		player->GetCollider()->MoveCollider(player->GetPlayerPosition());

		if (arrowForwards)
		{
			arrowMove += 0.2;
			if (arrowMove >= 3.1)
			{
				arrowForwards = false;
			}
		}
		else
		{
			arrowMove -= 0.2;
			if (arrowMove <= -3.1)
			{
				arrowForwards = true;
			}
		}
		arrow->setPosition(sf::Vector2f(arrow->getPosition().x + arrowMove, arrow->getPosition().y));

		// Drawing everything
		window->clear();
		windowDebug->clear();

		debug->Draw(windowDebug);

		level->Draw(window);

		if (level->levelIndex != -3)
		{
			if (door->DoorIsOpen() && level->levelIndex != -1)
			{
				window->draw(*arrow);
			}

			for (auto& itr : interacts)
			{
				window->draw(*itr->GetSprite());
				if (itr->m_isDoor)
				{
					if (enemies.size() == 0 && itr->Interact(player->GetPlayerPosition(), itr->GetInteractPos()))
					{
						window->draw(*player->GetInteractSprite());
					}
				}
				else if (itr->Interact(player->GetPlayerPosition(), itr->GetInteractPos()) && itr->m_interacted == false)
				{
					window->draw(*player->GetInteractSprite());
				}
			}

			window->draw(*player->GetSprite());

			for (auto& itr : enemies)
			{
				itr->GetCollider()->MoveCollider(itr->GetEnemyPosition());

				window->draw(*itr->GetSprite());

				itr->UpdateEnemy(player->GetPlayerPosition());
			}

			for (auto& itr : bullets)
			{
				itr->UpdateBullet();
				window->draw(*itr->GetSprite());
			}

			for (auto& itr : interacts)
			{
				itr->Update();
			}

			// Drawing colliders if enabled
			player->GetCollider()->DrawColliders(window, debug->m_showColliders);

			level->GetCollider()->DrawColliders(window, debug->m_showColliders);

			for (auto& itr : enemies)
			{
				itr->GetCollider()->DrawColliders(window, debug->m_showColliders);
			}

			i = 0;
			for (auto& itr : hearts)
			{
				i++;
				if (i <= player->PlayerGetHealthCurrent())
				{
					itr->setTexture(*heartTexture);
				}
				else
				{
					itr->setTexture(*heartNullTexture);
				}
				itr->setPosition(100 + 40 * i, 19);
				window->draw(*itr);
			}

			window->draw(*door->GetSprite());
		}

		for (auto& itr : particleManagerVec)
		{
			for (auto& itr2 : itr->GetParticles())
			{
				itr2->Update();
				window->draw(*itr2->GetParticle());
			}
		}

		window->draw(cursor);

		window->draw(trans);

		window->display();
		windowDebug->display();

		for (itParticleManagerVec = particleManagerVec.begin(); itParticleManagerVec != particleManagerVec.end(); itParticleManagerVec++)
		{
			if ((*itParticleManagerVec)->IsFinished())
			{
				delete *itParticleManagerVec;
				*itParticleManagerVec = nullptr;
				particleManagerVec.erase(itParticleManagerVec);
				break;
			}
		}
	}

	// Deallocating memory
	for (auto& itr : particleManagerVec)
	{
		delete itr;
		itr = nullptr;
	}
	particleManagerVec.clear();

	for (auto& itr : enemies)
	{
		delete itr;
		itr = nullptr;
	}
	enemies.clear();

	for (auto& itr : bullets)
	{
		delete itr;
		itr = nullptr;
	}
	bullets.clear();

	for (auto& itr : interacts)
	{
		delete itr;
		itr = nullptr;
	}

	delete level, player, debug;
	level = nullptr;
	player = nullptr;
	debug = nullptr;
}

Manager::Manager()
{
	i = 0;

	// Creating render window in 720p, setting style to only be able to close, not resise or maximise
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "deez nuts", sf::Style::Close);

	// Setting window frame limit for reasonable and consistent speed values
	window->setFramerateLimit(60);

	// Creating debug window with same style but smaller resolution
	windowDebug = new sf::RenderWindow(sf::VideoMode(500, 500), "debug", sf::Style::Close);

	// Creating debug window object to access the methods and data
	debug = new DebugWindow();

	zoom = new sf::View(window->getView());

	window->setView(*zoom);

	particleManager = nullptr;

	arrow = new sf::Sprite();
	arrowImage = new sf::Image();
	arrowTexture = new sf::Texture();

	heart = new sf::Sprite();
	heartImage = new sf::Image();
	heartTexture = new sf::Texture();

	heartNullImage = new sf::Image();
	heartNullTexture = new sf::Texture();
	
	if (!arrowImage->loadFromFile("sprites/arrow.png"))
	{
		std::cout << "Error: arrow image loading";
	}

	arrowImage->createMaskFromColor(sf::Color::Blue);
	arrowTexture->loadFromImage(*arrowImage);
	arrow->setTexture(*arrowTexture);

	arrow->setOrigin(arrow->getGlobalBounds().width, arrow->getGlobalBounds().height / 2);

	arrow->setPosition(sf::Vector2f(1200, 360));

	if (!heartImage->loadFromFile("sprites/heart.png"))
	{
		std::cout << "Error: heart image loading";
	}

	heartImage->createMaskFromColor(sf::Color::Blue);
	heartTexture->loadFromImage(*heartImage);
	heart->setTexture(*heartTexture);

	if (!heartNullImage->loadFromFile("sprites/heart_null.png"))
	{
		std::cout << "Error: heart image loading";
	}

	heartNullImage->createMaskFromColor(sf::Color::Blue);
	heartNullTexture->loadFromImage(*heartNullImage);

	heart->setOrigin(heart->getGlobalBounds().width / 2, heart->getGlobalBounds().height / 2);
	heart->setPosition(sf::Vector2f(100, 19));
	hearts.push_back(heart);
	heart->setPosition(sf::Vector2f(140, 19));
	hearts.push_back(heart);
	heart->setPosition(sf::Vector2f(180, 19));
	hearts.push_back(heart);
}

Manager::~Manager()
{
	delete arrow, arrowImage, arrowTexture, heart, heartImage, heartTexture, window, windowDebug, debug, particleManager;
	arrow = nullptr;
	arrowImage = nullptr;
	arrowTexture = nullptr;
	heart = nullptr;
	heartImage = nullptr;
	heartTexture = nullptr;
	window = nullptr;
	windowDebug = nullptr;
	debug = nullptr;
	particleManager = nullptr;
}
