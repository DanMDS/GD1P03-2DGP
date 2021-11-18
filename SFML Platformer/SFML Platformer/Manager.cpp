#include "Manager.h"

Manager::Manager()
{
	// Initialising main and debug windows
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "deez nuts", sf::Style::Fullscreen);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(60);
	view = window->getView();
	view.zoom(1);
	window->setView(view);

	// Initialising debug variables to 0 since they will get set in the debugs constructor
	m_rocketSpeed = 0;
	m_turretAlertDist = 0;
	m_turretShootCooldown = 0;

	// Initialsing bool to avoid warnings
	m_timeTrialsUnlocked = false;

	// Setting up time trial timer
	if (!m_font.loadFromFile("ARIAL.ttf"))
	{
		std::cout << "Error loading font";
	}
	m_timerText.setString("null");
	m_timerText.setFont(m_font);
	m_timerText.setCharacterSize(25);
	m_timerText.setFillColor(sf::Color::Green);
	m_timerText.setOutlineColor(sf::Color::Black);
	m_timerText.setOutlineThickness(2);

	m_trialTime = 20.0f;

	m_shootCooldown = 500;

	// Loading progress from file
	m_iniIn.open("files/progress.ini");
	if (!m_iniIn.is_open())
	{
		std::cout << "Error loading initialisation file";
	}
	else
	{
		m_iniIn >> m_levelsUnlocked;
		m_iniIn.ignore(100, '\n');
		m_iniIn >> m_timeTrialsUnlocked;
		m_iniIn.ignore(100, '\n');
		m_iniIn >> m_currentLevel;
		m_iniIn.ignore(100, '\n');
		for (int i = 0; i < 5; i++)
		{
			m_iniIn >> m_timeTrialComplete[i];
		}
		m_iniIn.ignore(100, '\n');
		m_iniIn >> m_soundVolume;
		m_iniIn.ignore(100, '\n');
		m_iniIn >> m_musicVolume;
	}

	m_levelsUnlocked += 1;
	std::cout << "Levels unlocked: " << m_levelsUnlocked << "\n";

	// Loading sound settings from file
	m_soundIn.open("files/sound.ini");
	if (m_soundIn.is_open())
	{
		m_soundIn >> m_soundVolume;
		m_soundIn.ignore(100, '\n');
		m_soundIn >> m_musicVolume;
	}
	else
	{
		std::cout << "Error opening sound settings file";
	}
	m_soundIn.close();

	contSet.antialiasingLevel = 8;

	canJump = false;
	changeLevel = false;
	deleteThis = false;

	m_soundManager = new SoundManager(&m_soundVolume, &m_musicVolume);

	// Creating world
	m_scale = 30.0f;
	b2Vec2 m_Gravity(0.0f, 50.0f);
	world = new b2World(m_Gravity);
	contactListener = new PlayerContactListener(m_soundManager);
	world->SetContactListener(contactListener);

	// Initialising class objects
	player = new Player(b2Vec2(300, 400), m_soundManager, world, m_scale);
	ObjVec.push_back(player);

	menu = new Menu(window, m_timeTrialsUnlocked, &view, &m_levelsUnlocked, &m_timeTrialComplete, &m_currentLevel, m_soundManager, &m_soundVolume, &m_musicVolume);

	levelManager = new LevelManager(window, &grappleVec, &levelObjVec, &ObjVec, &turretVec, &m_levelsUnlocked, &m_currentLevel, &m_turretShootCooldown, &m_turretAlertDist, &m_rocketSpeed, m_soundManager, menu, player, world, m_scale);

	goal = new Goal(sf::Vector2f(0, 0), player, levelManager, &partVec, &m_timeTrialComplete, m_soundManager);
	checkpoint = new Goal(sf::Vector2f(0, 0), player, levelManager, &partVec, &m_timeTrialComplete, m_soundManager, true);

	m_shootTimer = clock.getElapsedTime();

	m_trialTimer = clock.getElapsedTime();
	
	debug = new Debug(player, &m_turretShootCooldown, &m_turretAlertDist, &m_shootCooldown, &m_rocketSpeed);
}

Manager::~Manager()
{
	// Updating initialisation file
	m_iniOut.open("files/progress.ini");

	if (m_levelsUnlocked >= 5)
	{
		m_timeTrialsUnlocked = true;
	}

	if (m_iniOut.is_open())
	{
		m_iniOut 
			<< m_levelsUnlocked - 1 << " // Levels Completed\n"
			<< m_timeTrialsUnlocked << " // Time Trials Unlocked\n"
			<< m_currentLevel << " // Current Level\n";

		for (int i = 0; i < 5; i++)
		{
			m_iniOut << m_timeTrialComplete[i] << " ";
		}
		m_iniOut << "// Time Trials Completed\n";
	}
	else
	{
		std::cout << "Error opening progress initialisation file";
	}
	m_iniOut.close();

	m_soundOut.open("files/sound.ini");
	if (m_soundOut.is_open())
	{
		m_soundOut << m_soundVolume << " // Sound Volume\n" << m_musicVolume << " // Music Volume";
	}

	// Deallocating memory
	delete window;
	delete player;
	delete menu;
	delete levelManager;
	delete goal;
	delete checkpoint;
	delete world;
	delete contactListener;
	delete debug;
	delete m_soundManager;

	window = nullptr;
	player = nullptr;
	menu = nullptr;
	levelManager = nullptr;
	goal = nullptr;
	checkpoint = nullptr;
	world = nullptr;
	contactListener = nullptr;
	debug = nullptr;
	m_soundManager = nullptr;
}

void Manager::RunGame()
{
	// Running main menu
	levelManager->ChangeLevel(menu->RunMenu());

	// Exiting function if 'exit' menu option is selected and window is closed
	if (!window->isOpen()) { return; }

	// Centering camera on player
	view.setCenter(sf::Vector2f(player->GetShape()->getPosition().x, player->GetShape()->getPosition().y));

	// Activating non-death transition for player (green colour) 
	// and starting it on max size to match with menu fadeout
	player->Transition(false);
	player->GetTrans()->setScale(200, 200);

	// Game loop
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					for (auto& itr : grappleVec)
					{
						itr->GrappleStart();
					}
					//player->Transition(false);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					for (auto& itr : grappleVec)
					{
						itr->GrappleEnd();
					}
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					// Running main menu
					levelManager->ChangeLevel(menu->RunMenu());

					// Exiting function if 'exit' menu option is selected and window is closed
					if (!window->isOpen()) { return; }

					// Centering camera on player
					view.setCenter(sf::Vector2f(player->GetShape()->getPosition().x, player->GetShape()->getPosition().y));

					// Activating non-death transition for player (green colour) 
					// and starting it on max size to match with menu fadeout
					player->Transition(false);
					player->GetTrans()->setScale(200, 200);
				}

				if (event.key.code == sf::Keyboard::P)
				{
					debug->OpenWindow();
				}
			}
		}

		mousePos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window)));

		// Shooting
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asMilliseconds() - m_shootTimer.asMilliseconds() > m_shootCooldown)
		{
			m_shootTimer = clock.getElapsedTime();
			m_soundManager->PlaySoundShootPlayer();
			ObjVec.push_back(new Rocket(mousePos, player->GetSprite()->getPosition(), player, m_rocketSpeed));
		}

		// Setting up time trials
		checkpoint->IsTimeTrialActive(menu->TimeTrialsActive());
		goal->IsTimeTrialActive(menu->TimeTrialsActive());

		// Setting timer for time trials
		if (m_trialTime - m_trialClock.getElapsedTime().asSeconds() - m_trialTimer.asSeconds() <= 0 && menu->TimeTrialsActive() && !player->IsDead())
		{
			m_trialClock.restart();
			player->Transition(true);
		}

		if (player->GetB2d()->GetBody()->GetType() == b2_kinematicBody)
		{
			m_trialClock.restart();
			m_trialTimer = m_trialClock.getElapsedTime();
		}

		// Enabling menu
		if (menu->InMenu()) { levelManager->ChangeLevel(menu->RunMenu()); }

		// Allowing player control only if not grappling to anything
		bool playerMove = true;
		for (auto& itr : grappleVec)
		{
			if (itr->Grappling()) { playerMove = false; break; }
		}

		if (playerMove) { player->PlayerControls(contactListener->IsGrounded()); }

		window->clear(sf::Color(200, 200, 200));

		// Moving goal and checkpoint here due to unknown include errors
		switch (levelManager->GetIndex())
		{
		case 1:
			goal->GetSprite()->setPosition(7250, -50);
			checkpoint->GetSprite()->setPosition(4000, -50);
			break;
		case 2:
			goal->GetSprite()->setPosition(4600, -350);
			checkpoint->GetSprite()->setPosition(800, -450);
			break;
		case 3:
			goal->GetSprite()->setPosition(3300, -50);
			checkpoint->GetSprite()->setPosition(2800, -50);
			break;
		case 4:
			goal->GetSprite()->setPosition(850, 150);
			checkpoint->GetSprite()->setPosition(0, -550);
			break;
		case 5:
			goal->GetSprite()->setPosition(0, -2900);
			checkpoint->GetSprite()->setPosition(0, -2050);
			break;
		}
		goal->Update();
		checkpoint->Update();

		for (ObjVecIt = ObjVec.begin(); ObjVecIt != ObjVec.end(); ObjVecIt++)
		{
			(*ObjVecIt)->Update();
			switch ((*ObjVecIt)->GetTag())
			{
			case Tag::Rocket:
				for (auto& itr : levelObjVec)
				{
					if ((*ObjVecIt)->GetSprite()->getGlobalBounds().intersects(itr->GetShape()->getGlobalBounds()))
					{
						deleteThis = true;
						m_soundManager->PlaySoundExlode();
						partVec.push_back(new ParticleManager((sf::Color::Red), (*ObjVecIt)->GetSprite()->getPosition(), 10));
						partVec.push_back(new ParticleManager((sf::Color::Yellow), (*ObjVecIt)->GetSprite()->getPosition(), 5));
					}
				}
				break;

			case Tag::Player:
				view.setCenter(player->GetSprite()->getPosition());
				window->setView(view);
				continue;
			}
			if (deleteThis)
			{
				delete* ObjVecIt;
				*ObjVecIt = nullptr;
				ObjVec.erase(ObjVecIt);
				deleteThis = false;
				break;
			}
			window->draw(*(*ObjVecIt)->GetSprite());
		}
		window->draw(*goal->GetSprite());
		window->draw(*checkpoint->GetSprite());

		for (auto& itr : turretVec)
		{
			itr->Update();
			window->draw(*itr->GetSprite());
			window->draw(*itr->GetGun());
		}

		for (auto& itr : levelObjVec)
		{
			itr->Update();
			if (itr->GetTag() == Tag::GrapplePoint)
			{
				window->draw(*itr->GetSprite());
				continue;
			}
			if (itr->GetTag() == Tag::LevelObstacleKill && itr->GetShape()->getGlobalBounds().intersects(player->GetSprite()->getGlobalBounds()) && !player->IsDead())
			{
				player->Transition(true);
			}
			window->draw(*itr->GetShape());
		}

		for (auto& itr : grappleVec)
		{
			itr->Update(window);
		}

		window->draw(levelManager->GetLevelText());

		if (levelManager->GetIndex() == 1)
		{
			for (auto itr : levelManager->GetTutorialText())
			{
				window->draw(itr);
			}
		}


		for (partVecIt = partVec.begin(); partVecIt != partVec.end(); partVecIt++)
		{
			if ((*partVecIt)->IsFinished())
			{
				delete (*partVecIt);
				(*partVecIt) = nullptr;
				partVec.erase(partVecIt);
				break;
			}
		}
		for (auto& itra : partVec)
		{
			for (auto& itrb : itra->GetParticles())
			{
				itrb->Update();
				window->draw(*itrb->GetParticle());
			}
		}

		if (player->IsDead())
		{
			window->draw(*player->GetTrans());
		}
		window->draw(*player->GetSprite());

		/*if (int(m_trialTime - m_trialClock.getElapsedTime().asSeconds() - m_trialTimer.asSeconds() + 1 == 3 && m_playTimerSound1)
		{

		}*/

		m_timerText.setString("Time remaining: " + std::to_string(int(m_trialTime - m_trialClock.getElapsedTime().asSeconds() - m_trialTimer.asSeconds() + 1)));
		m_timerText.setPosition(sf::Vector2f(view.getCenter().x - 900, view.getCenter().y - 500));

		if (menu->TimeTrialsActive()) { window->draw(m_timerText); }

		window->display();

		world->Step(1.0f / 60.0f, 10, 30);
	}

	for (auto& itr : ObjVec)
	{
		if (itr->GetTag() != Tag::Player)
		{
			delete itr;
			itr = nullptr;
		}
	}
	delete player;
	player = nullptr;
	ObjVec.clear();
}