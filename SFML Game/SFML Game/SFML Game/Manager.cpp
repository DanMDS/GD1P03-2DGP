#include "Manager.h"
#include <iostream>

bool Manager::CollisionBulletEnemy(Bullet _bullet, Enemy _enemy)
{
	// Checking enemy to bullet collisions
	if (_bullet.GetSprite()->getGlobalBounds().intersects(_enemy.GetSprite()->getGlobalBounds()))
	{
		return true;
	}
	return false;
}

float Manager::GetPlayerDistance(sf::Vector2f* _playerPos, sf::Vector2f* _entityPos)
{
	// Getting player distance from a point
	int xDifference = int(_playerPos->x - _entityPos->x);
	int yDifference = int(_playerPos->y - _entityPos->y);

	return static_cast<float>(sqrt(abs(xDifference) ^ 2 + abs(yDifference) ^ 2));
}

void Manager::ChangeLevel(int _index)
{
	// Checking what next level should be, placing enemies and buttons accordingly
	if (level->GetLevelIndex() >= 0 && _index == -4)
	{
		m_levelsCompleted += 1;
	}

	// Deleting enemies and bullets so that they dont carry over to the next level
	// Enemies are being deleted for use of debug controls
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

	// Randomising level or setting specific one, depending on _index
	level->ChangeLevel(player, enemies, _index);

	// Deleting interactables
	while (interacts.size() != 1)
	{
		for (itInteracts = interacts.begin(); itInteracts != interacts.end(); itInteracts++)
		{
			if (!(*itInteracts)->GetIsDoor())
			{
				delete* itInteracts;
				*itInteracts = nullptr;
				interacts.erase(itInteracts);
				break;
			}
		}
	}

	// Placing enemies depending of level index
	switch (level->GetLevelIndex())
	{
	case -3:
		// Start screen
		m_levelsCompleted = 0;

		break;
	case -2:
		// Tutorial screen
		m_levelsCompleted = 0;

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(800, 200), true);
		enemies.push_back(enemy);

		button = new Button(sf::Vector2f(800, 350));
		interacts.push_back(button);

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
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(140, 80));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(200, 80));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(260, 80));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(140, 640));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(200, 640));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(260, 640));
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(80, 80), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 80), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 640), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(80, 640), true);
		enemies.push_back(enemy);

		break;
	case 3:
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(80, 80), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 640), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 80), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(80, 640), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(650, 640), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(650, 80), true);
		enemies.push_back(enemy);

		break;
	case 4:
		button = new Button(sf::Vector2f(640, 640));
		interacts.push_back(button);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(420, 100), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(860, 100), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(600, 550), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(640, 550), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(680, 550), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(800, 550), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(840, 550), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(880, 550), true);
		enemies.push_back(enemy);

		break;
	case 5:
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 320), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1200, 400), true);
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1160, 320), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1160, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1160, 400), true);
		enemies.push_back(enemy);

		button = new Button(sf::Vector2f(1000, 360));
		interacts.push_back(button);

		break;
	case 6:
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 120));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 180));
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
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 540));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 600));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 660));
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 240), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 300), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 420), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 480), true);
		enemies.push_back(enemy);
		break;
	case 7:
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1040, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(980, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(920, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(860, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(800, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(740, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(680, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(620, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(560, 60));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(500, 60));
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1040, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(980, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(920, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(860, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(800, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(740, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(680, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(620, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(560, 660));
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(500, 660));
		enemies.push_back(enemy);

		break;
	case 8:
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1160, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1100, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(1040, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(980, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(920, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(860, 360), true);
		enemies.push_back(enemy);

		break;
	case 9:
		button = new Button(sf::Vector2f(640, 360));
		interacts.push_back(button);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(475, 280), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(475, 320), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(475, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(475, 400), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(475, 440), true);
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(805, 280), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(805, 320), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(805, 360), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(805, 400), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(805, 440), true);
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(560, 200), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(600, 200), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(640, 200), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(680, 200), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(720, 200), true);
		enemies.push_back(enemy);

		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(560, 520), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(600, 520), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(640, 520), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(680, 520), true);
		enemies.push_back(enemy);
		enemy = new Enemy("sprites/enemy.png", sf::Vector2f(720, 520), true);
		enemies.push_back(enemy);

		break;
	}
}

void CollisionEnemies(Enemy* _enemy1, Enemy* _enemy2)
{
	// Checking for enemy to enemy collisions
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
	// Checking for player to wall collisions
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
	// Checking for enemy to wall collisions
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
	// Checkign for player to enemy collisions
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
	// Starting debug window closed
	windowDebug->setVisible(false);

	// Making the cursor invisible for the main window
	window->setMouseCursorVisible(false);
	windowDebug->setMouseCursorVisible(false);

	// Setting random seed to current time to ensure a different result each time
	srand(static_cast<unsigned int>(time(NULL)));
	
	// Getting mouse position for later use
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	// Creating sample shape for testing mouse position
	sf::CircleShape cursor(5);
	cursor.setFillColor(sf::Color::Magenta);
	cursor.setOutlineColor(sf::Color::Black);
	cursor.setOutlineThickness(1);
	cursor.setOrigin(5, 5);

	// Setting colour of trans
	trans->setFillColor(sf::Color(0, 0, 0, 0));

	// Setting player timer
	player->timer = player->clock.getElapsedTime();

	// Game loop
	while (window->isOpen())
	{
		// Setting zoom levels for after hit effect
		window->setView(*zoom);

		if (player->m_zoomed)
		{
			zoom->setCenter(sf::Vector2f(1280 / 2, 720 / 2));
			zoom->setSize(sf::Vector2f(1280, 720));
		}

		// Changing opacity of transition rect
		if (isTrans)
		{
			if (fadeClock.getElapsedTime().asMilliseconds() > 1 && alpha != 255)
			{
				trans->setFillColor(sf::Color(0, 0, 0, alpha));
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
			trans->setFillColor(sf::Color(0, 0, 0, alpha));
			alpha = (alpha - 20 < 0) ? 0 : alpha - 20;
			fadeClock.restart();
		}

		// Getting mouse position for use
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
				windowDebug->close();
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
						if (itr->Interact(player->GetPlayerPosition(), itr->GetInteractPos()) && itr->GetInteracted() == false)
						{
							if (itr->GetIsDoor() && level->GetLevelIndex() != -3 && level->LevelEndCheck(enemies.size(), interacts))
							{
								soundManager->PlaySoundDoor();
								isTrans = true;
							}
							else if (level->GetLevelIndex() == -1)
							{
								soundManager->PlaySoundDoor();
								player->ResetPlayerState();
								itr->SetInteracted(true);
								isTrans = true;
							}
							else
							{
								soundManager->PlaySoundButton();
								itr->SetInteracted(true);
							}
						}
					}
				}

				// M: Muting/unmuting music
				if (event.key.code == sf::Keyboard::M)
				{
					m_isMusic = !m_isMusic;
				}
				soundManager->SetMusicVolume(m_isMusic ? 10.0f : 0.0f);

				// Debug controls
				if (event.key.code == sf::Keyboard::Escape)
				{
					windowDebug->setVisible(true);
					window->setMouseCursorVisible(true);
					windowDebug->setMouseCursorVisible(true);
					m_showDebug = !m_showDebug;
				}

				if (debug->GetDebugControls())
				{
					// T: Run change level event to change to a random level and reset the players position
					if (event.key.code == sf::Keyboard::T)
					{
						ChangeLevel(-4);
					}

					// Numbers 0 - 9: Changing to specific level
					if (event.key.code == sf::Keyboard::Num0)
					{
						ChangeLevel(0);
					}
					if (event.key.code == sf::Keyboard::Num1)
					{
						ChangeLevel(1);
					}
					if (event.key.code == sf::Keyboard::Num2)
					{
						ChangeLevel(2);
					}
					if (event.key.code == sf::Keyboard::Num3)
					{
						ChangeLevel(3);
					}
					if (event.key.code == sf::Keyboard::Num4)
					{
						ChangeLevel(4);
					}
					if (event.key.code == sf::Keyboard::Num5)
					{
						ChangeLevel(5);
					}
					if (event.key.code == sf::Keyboard::Num6)
					{
						ChangeLevel(6);
					}
					if (event.key.code == sf::Keyboard::Num7)
					{
						ChangeLevel(7);
					}
					if (event.key.code == sf::Keyboard::Num8)
					{
						ChangeLevel(8);
					}
					if (event.key.code == sf::Keyboard::Num9)
					{
						ChangeLevel(9);
					}
				}
			}

			// main menu buttons and debug enemy spawn
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && debug->GetSpawnEnemy() && enemies.size() < 20)
				{
					if (debug->GetShootingEnemy())
					{
						enemy = new Enemy("sprites/enemy.png", sf::Vector2f(mousePos), true);
						enemies.push_back(enemy);
					}
					else
					{
						enemy = new Enemy("sprites/enemy.png", sf::Vector2f(mousePos));
						enemies.push_back(enemy);
					}
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && level->GetLevelIndex() == -3)
				{
					if (m_beginButton->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
					{
						soundManager->PlaySoundDoor();
						isTrans = true;
					}
					else if (m_endButton->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
					{
						window->close();
					}
				}
			}
		}

		// Changing level, random if not on death screen
		if (alpha == 255 && !player->IsDead())
		{
			if (level->GetLevelIndex() == -1)
			{
				ChangeLevel(-3);
			}
			else if (level->GetLevelIndex() == -3)
			{
				ChangeLevel(-2);
			}
			else
			{
				ChangeLevel(-4);
			}
		}

		// Death event
		if (player->IsDead() && level->GetLevelIndex() != -1)
		{
			if (!isTrans)
			{
				soundManager->PlaySoundLose();
			}
			isTrans = true;
			if (alpha == 255)
			{
				ChangeLevel(-1);
			}
		}

		// Returning to main menu
		if (level->GetLevelIndex() == -1 && alpha == 255 && level->LevelEndCheck(enemies.size(), interacts))
		{
			ChangeLevel(-3);
		}

		// Shooting, limited to once every 500 milliseconds
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (player->clock.getElapsedTime().asMilliseconds() - player->shootTimer.asMilliseconds() > m_fireDelayPlayer)
			{
				if (level->GetLevelIndex() != -3)
				{
					soundManager->PlaySoundShootPlayer();
				}
				player->shootTimer = player->clock.getElapsedTime();
				bullet = new Bullet(float(m_bulletSpeedPlayer), true, player->GetPlayerPosition(), sf::Vector2f(mousePos));
				bullets.push_back(bullet);
			}
		}

		// Enemy shooting
		for (auto& itr : enemies)
		{
			if (itr->GetEnemyShoot())
			{
				soundManager->PlaySoundShootEnemy();
				bullet = new Bullet(float(3.0f + (m_levelsCompleted * 0.3)), false, itr->GetEnemyPosition(), player->GetPlayerPosition());
				bullets.push_back(bullet);
				itr->SetEnemyShoot(false);
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
						particleManager = new ParticleManager(sf::Color::Green, (*itBullets)->GetSprite()->getPosition(), 5);
						particleManagerVec.push_back(particleManager);
					}
					else
					{
						particleManager = new ParticleManager(sf::Color::Red, (*itBullets)->GetSprite()->getPosition(), 5);
						particleManagerVec.push_back(particleManager);
					}
					Bullet* temp = *itBullets;
					delete temp;
					temp = nullptr;
					bullets.erase(itBullets);
					soundManager->PlaySoundHitWall();
					break;
				}
			}
		}

		for (itBullets = bullets.begin(); itBullets != bullets.end(); ++itBullets)
		{
			if (!(*itBullets)->isFriendly() && player->GetSprite()->getGlobalBounds().intersects((*itBullets)->GetSprite()->getGlobalBounds()))
			{
				particleManager = new ParticleManager(sf::Color::Red, (*itBullets)->GetSprite()->getPosition(), 5);
				particleManagerVec.push_back(particleManager);
				if (!player->IsInv() && !isTrans && level->GetLevelIndex() != -2)
				{
					player->UpdateInv(zoom);
				}
				delete *itBullets;
				*itBullets = nullptr;
				bullets.erase(itBullets);
				soundManager->PlaySoundHitPlayer();
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
					particleManager = new ParticleManager(sf::Color::Green, (*itBullets)->GetSprite()->getPosition(), 5);
					particleManagerVec.push_back(particleManager);
					delete *itEnemies;
					*itEnemies = nullptr;
					delete *itBullets;
					*itBullets = nullptr;
					enemies.erase(itEnemies);
					bullets.erase(itBullets);
					collision = true;
					soundManager->PlaySoundHitEnemy();
					break;
				}
			}
			if (collision)
			{
				collision = false;
				break;
			}
			CollisionWall(*itEnemies, level);
			if (player->GetSprite()->getGlobalBounds().intersects((*itEnemies)->GetSprite()->getGlobalBounds()) && !isTrans)
			{
				if (player->IsInv() && level->GetLevelIndex() != -2)
				{
					(*itEnemies)->SetPlayerCollision(true);
				}
				else
				{
					soundManager->PlaySoundHitEnemy();
					if (level->GetLevelIndex() != -2)
					{
						if (!isTrans)
						{
							player->UpdateInv(zoom);
						}
					}
					delete * itEnemies;
					*itEnemies = NULL;
					enemies.erase(itEnemies);
					break;
				}
			}
			else
			{
				(*itEnemies)->SetPlayerCollision(false);
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
		while (m_showDebug)
		{
			windowDebug->clear();
			debug->Draw(windowDebug);
			while (windowDebug->pollEvent(eventDebug))
			{
				debug->Update(windowDebug, sf::Vector2f(mousePos), (eventDebug.type == sf::Event::MouseButtonPressed && eventDebug.key.code == sf::Mouse::Left), m_fireDelayPlayer, player->PlayerGetSpeed(), m_bulletSpeedPlayer);

				if (eventDebug.type == sf::Event::Closed)
				{
					windowDebug->setVisible(false);
					window->setMouseCursorVisible(false);
					windowDebug->setMouseCursorVisible(false);
					m_showDebug = false;
				}

				if (eventDebug.type == sf::Event::KeyPressed && debug->GetValueChanging())
				{
					if (eventDebug.key.code == sf::Keyboard::Space)
					{
						if (debug->GetValueSelectedPos() == 390)
						{
							debug->SetValueSelectedPos(330);
						}
						else
						{
							debug->SetValueSelectedPos(debug->GetValueSelectedPos() + 30);
						}
					}
					if (eventDebug.key.code == sf::Keyboard::Up && debug->GetValueSelectedPos() == 330 && m_fireDelayPlayer < 2000)
					{
						m_fireDelayPlayer += 10;
					}
					if (eventDebug.key.code == sf::Keyboard::Down && debug->GetValueSelectedPos() == 330 && m_fireDelayPlayer > 100)
					{
						m_fireDelayPlayer -= 10;
					}

					if (eventDebug.key.code == sf::Keyboard::Up && debug->GetValueSelectedPos() == 360 && player->PlayerGetSpeed() < 8)
					{
						player->PlayerSetSpeed(1);
					}
					if (eventDebug.key.code == sf::Keyboard::Down && debug->GetValueSelectedPos() == 360 && player->PlayerGetSpeed() > 1)
					{
						player->PlayerSetSpeed(-1);
					}

					if (eventDebug.key.code == sf::Keyboard::Up && debug->GetValueSelectedPos() == 390 && m_bulletSpeedPlayer < 20)
					{
						m_bulletSpeedPlayer += 1;
					}
					if (eventDebug.key.code == sf::Keyboard::Down && debug->GetValueSelectedPos() == 390 && m_bulletSpeedPlayer > 1)
					{
						m_bulletSpeedPlayer -= 1;
					}
				}
			}
			windowDebug->display();
		}

		// Updating objects where needed
		if (!isTrans && level->GetLevelIndex() != -1)
		{
			door->Update(level->LevelEndCheck(enemies.size(), interacts), player->GetPlayerPosition(), player, enemies);
		}

		player->MovePlayer();
		player->UpdatePlayer(zoom);
		player->GetCollider()->MoveCollider(player->GetPlayerPosition());

		if (arrowForwards)
		{
			arrowMove += 0.2f;
			if (arrowMove >= 3.1)
			{
				arrowForwards = false;
			}
		}
		else
		{
			arrowMove -= 0.2f;
			if (arrowMove <= -3.1)
			{
				arrowForwards = true;
			}
		}
		arrow->setPosition(sf::Vector2f(arrow->getPosition().x + arrowMove, arrow->getPosition().y));

		// Drawing everything
		window->clear();

		level->Draw(window);

		if (level->GetLevelIndex() != -3)
		{
			if (door->DoorIsOpen() && level->GetLevelIndex() != -1)
			{
				window->draw(*arrow);
			}

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

			level->GetCollider()->DrawColliders(window, debug->GetShowColliders());

			for (auto& itr : interacts)
			{
				window->draw(*itr->GetSprite());
				if (itr->GetIsDoor())
				{
					if (enemies.size() == 0 && itr->Interact(player->GetPlayerPosition(), itr->GetInteractPos()))
					{
						window->draw(*player->GetInteractSprite());
					}
				}
				else if (itr->Interact(player->GetPlayerPosition(), itr->GetInteractPos()) && itr->GetInteracted() == false)
				{
					window->draw(*player->GetInteractSprite());
				}
			}

			player->GetCollider()->DrawColliders(window, debug->GetShowColliders());
			window->draw(*player->GetSprite());

			for (auto& itr : enemies)
			{
				itr->GetCollider()->DrawColliders(window, debug->GetShowColliders());
			}

			if (level->GetLevelIndex() >= 0 || level->GetLevelIndex() == -2)
			{
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
					itr->setPosition(float(150 + 40 * i), 19.0f);
					window->draw(*itr);
				}

				hud->UpdateHud(m_levelsCompleted + 1);
				hud->Draw(window);

				window->draw(*door->GetSprite());
			}
		}

		if (level->GetLevelIndex() == -1)
		{
			if (m_levelsCompleted > m_highScore)
			{
				m_highScore = m_levelsCompleted;
			}
			m_deathText->setString("Levels completed: " + std::to_string(m_levelsCompleted) + "\nHigh score: " + std::to_string(m_highScore));
			window->draw(*m_deathText);
		}

		for (auto& itr : particleManagerVec)
		{
			for (auto& itr2 : itr->GetParticles())
			{
				itr2->Update();
				window->draw(*itr2->GetParticle());
			}
		}

		if (level->GetLevelIndex() == -3)
		{
			window->draw(*m_beginButton);
			window->draw(*m_endButton);
		}

		window->draw(cursor);

		window->draw(*trans);

		window->display();
		windowDebug->display();

		// Deleting particles once finished
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
}

Manager::Manager()
{
	i = 0;

	m_levelsCompleted = 0;

	// Initialising title screen buttons
	m_beginButton = new sf::RectangleShape(sf::Vector2f(140, 75));
	m_beginButton->setFillColor(sf::Color::Transparent);
	m_beginButton->setOutlineColor(sf::Color::Black);
	m_beginButton->setOutlineThickness(3);
	m_beginButton->setPosition(310, 380);

	m_endButton = new sf::RectangleShape(sf::Vector2f(140, 75));
	m_endButton->setFillColor(sf::Color::Transparent);
	m_endButton->setOutlineColor(sf::Color::Black);
	m_endButton->setOutlineThickness(3);
	m_endButton->setPosition(770, 380);

	// Setting high score variable from 'highscore.xml' file
	fileIn.open("highscore.xml");

	m_highScore = 0;

	fileIn >> m_highScore;

	// Creating sound object
	soundManager = new SoundManager();

	// Creating player object, setting sprite and start position
	player = new Player("sprites/player.png", playerDefaultPos);

	// Creating enemy object
	enemy = nullptr;

	// Creating level object, setting start level to title screen
	level = new Level("levels/level_main.png");

	// Creating button object
	button = nullptr;

	// Creating bullet object
	bullet = nullptr;

	// Creating door object
	door = new Door(sf::Vector2i(m_windowDimX, m_windowDimY));
	interacts.push_back(door);

	// Creating HUD object
	hud = new Hud();

	m_isMusic = true;

	// Creating render window in 720p, setting style to only be able to close, not resise or maximise
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML Game", sf::Style::Close);

	// Setting window frame limit for reasonable and consistent speed values
	window->setFramerateLimit(60);

	// Creating debug window with same style but smaller resolution
	windowDebug = new sf::RenderWindow(sf::VideoMode(500, 500), "Debug Window", sf::Style::Close);

	// Creating debug window object to access the methods and data
	debug = new DebugWindow();

	// Creating text to be displayed on death screen
	font = new sf::Font();
	font->loadFromFile("fonts/AltoneTrial-Regular.ttf");

	m_deathText = new sf::Text("Levels completed: ", *font, 25);
	m_deathText->setFillColor(sf::Color::White);
	m_deathText->setOutlineColor(sf::Color::Black);
	m_deathText->setOutlineThickness(2);
	m_deathText->setPosition(525, 250);

	// Creating transition rect
	trans = new sf::RectangleShape(sf::Vector2f(1280, 720));

	// Creating view for hit effect
	zoom = new sf::View(sf::Vector2f(1280 / 2, 720 / 2), sf::Vector2f(1280, 720));

	window->setView(*zoom);

	// Initialsing particle manager
	particleManager = nullptr;

	// Lodaing sprites. textures and images for arrow and hearts
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
	// Stopping music
	soundManager->StopSounds();

	// Allowing sounds to close properly
	fadeClock.restart();

	// while (fadeClock.getElapsedTime().asMilliseconds() < 1000) {}

	// Setting high score in file
	fileOut.open("highscore.xml");
	fileOut << m_highScore;
	fileOut.close();
	fileIn.close();

	// Deallocating memory

	// Clearing vectors
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

	// Deleting individual class objects and arrow/heart textures, images and sprites
	delete trans;
	delete level;
	delete player;
	delete zoom;
	delete arrow;
	delete arrowImage;
	delete arrowTexture;
	delete heart;
	delete heartImage;
	delete heartTexture;
	delete window;
	delete windowDebug;
	delete hud;
	delete soundManager;
	delete debug;

	trans = nullptr;
	player = nullptr;
	level = nullptr;
	button = nullptr;
	zoom = nullptr;
	arrow = nullptr;
	arrowImage = nullptr;
	arrowTexture = nullptr;
	heart = nullptr;
	heartImage = nullptr;
	heartTexture = nullptr;
	window = nullptr;
	windowDebug = nullptr;
	debug = nullptr;
	hud = nullptr;
	soundManager = nullptr;
}
