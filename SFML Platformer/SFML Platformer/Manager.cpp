#include "Manager.h"

Manager::Manager()
{
	// Initialising window
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "deez nuts", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
	view = window->getView();
	view.zoom(1);
	window->setView(view);

	// Initialising bool arrays
	for (auto b : m_levelsCompletedArr)
	{
		b = false;
	}
	/*for (auto b : m_timeTrialComplete)
	{
		b = false;
	}*/

	m_iniIn.open("files/initialisation.ini");
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
		for (auto b : m_timeTrialComplete)
		{
			m_iniIn >> b;
		}
	}

	m_levelsUnlocked += 1;
	std::cout << "Levels unlocked: " << m_levelsUnlocked << "\n";

	for (int i = 0; i < m_levelsUnlocked; i++)
	{
		m_levelsCompletedArr[i] = true;
	}

	// Initialising other variables
	m_levelsUnlocked = 0;
	m_timeTrialsUnlocked = false;

	contSet.antialiasingLevel = 8;

	canJump = false;
	changeLevel = false;
	deleteThis = false;

	// Creating world
	m_scale = 30.0f;
	b2Vec2 m_Gravity(0.0f, 50.0f);
	world = new b2World(m_Gravity);
	contactListener = new PlayerContactListener();
	world->SetContactListener(contactListener);

	// Initialising class object
	player = new Player(b2Vec2(300, 400), world, m_scale);
	ObjVec.push_back(player);

	menu = new Menu(window, m_timeTrialsUnlocked, &view, &m_levelsCompletedArr, &m_timeTrialComplete, &m_currentLevel);

	levelManager = new LevelManager(window, &grappleVec, &levelObjVec, &ObjVec, &turretVec, &m_levelsCompletedArr, &m_currentLevel, menu, player, world, m_scale);

	goal = new Goal(sf::Vector2f(0, 0), player, levelManager, &partVec);
	checkpoint = new Goal(sf::Vector2f(0, 0), player, levelManager, &partVec, true);
}

Manager::~Manager()
{
	// Updating initialisation file
	m_levelsUnlocked = 0;
	for (auto b : m_levelsCompletedArr)
	{
		m_levelsUnlocked += b;
	}

	m_iniOut.open("files/initialisation.ini");

	if (m_iniOut.is_open())
	{
		m_iniOut << m_levelsUnlocked - 1
			<< "//Levels Completed\n"
			<< m_timeTrialsUnlocked
			<< "//Time Trials Unlocked\n"
			<< m_currentLevel
			<< "//Current Level\n";

		for (int i = 0; i < 5; i++)
		{
			m_iniOut << m_timeTrialComplete[i] << " ";
		}
		m_iniOut << "//Time Trials Completed\n";
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

	window = nullptr;
	player = nullptr;
	menu = nullptr;
	levelManager = nullptr;
	goal = nullptr;
	checkpoint = nullptr;
	world = nullptr;
	contactListener = nullptr;
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
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					ObjVec.push_back(new Rocket(mousePos, player->GetSprite()->getPosition(), player));
				}
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
			}
		}
		mousePos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window)));
		
		//if (player->IsMidTrans() && !player->isTransDone())
		//{
		//	changeLevel = true;
		//}

		//if (player->IsMidTrans() && changeLevel && player->isTransDone())
		//{
		//	levelManager->ChangeLevel(-1);
		//	changeLevel = false;
		//}

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