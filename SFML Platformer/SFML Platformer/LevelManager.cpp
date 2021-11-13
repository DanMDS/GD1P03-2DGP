#include "LevelManager.h"

LevelManager::LevelManager(sf::RenderWindow* _window, std::vector<GrapplePoint*>* _grappleVec, std::vector<Object*>* _levelObjVec, std::vector<Object*>* _objVec, std::vector<Turret*>* _turretVec, bool(*_levelsCompleted)[5], int* _currentLevel, Menu* _menu, Player* _player, b2World* _world, const float& _scale)
{
	// Setting pointers and references
	m_levelIndex = 1;
	levelObjVec = _levelObjVec;
	objVec = _objVec;
	grappleVec = _grappleVec;
	turretVec = _turretVec;
	player = _player;
	world = _world;
	m_scale = _scale;
	window = _window;
	m_currentLevel = _currentLevel;
	m_levelsCompleted = _levelsCompleted;
	m_menu = _menu;

	// Setting up timer
	m_timerText.setString("Timer: " + std::to_string(m_timer));
	m_timerText.setFont(font);
	m_timerText.setCharacterSize(fontSize);
	m_timerText.setFillColor(sf::Color::Green);
	m_timerText.setOutlineColor(sf::Color::Black);
	m_timerText.setOutlineThickness(2);

	// Setting tutorial text, loaded from files
	levelText.setString("null");
	if (!font.loadFromFile("ARIAL.ttf"))
	{
		printf("Error loading font");
	}
	fontSize = 25;

	fileIn.open("files/tutorial_jump.txt");

	if (fileIn.is_open())
	{
		while (fileIn.good())
		{
			fileIn >> fileInput;
			if (fileInput == "/")
			{
				tutorialText += "\n";
			}
			else
			{
				tutorialText += fileInput + " ";
			}
		}
		std::cout << tutorialText;
	}
	else
	{
		std::cout << "Error opening tutorial text file: jump";
	}

	jump.setFont(font);
	jump.setCharacterSize(fontSize);
	jump.setFillColor(sf::Color::Green);
	jump.setOutlineColor(sf::Color::Black);
	jump.setOutlineThickness(2);
	jump.setString(tutorialText);

	fileIn.close();

	fileIn.open("files/tutorial_shoot.txt");

	tutorialText = "";

	if (fileIn.is_open())
	{
		while (fileIn.good())
		{
			fileIn >> fileInput;
			if (fileInput == "/")
			{
				tutorialText += "\n";
			}
			else
			{
				tutorialText += fileInput + " ";
			}
		}
		std::cout << tutorialText;
	}
	else
	{
		std::cout << "Error opening tutorial text file: shoot";
	}

	shoot.setFont(font);
	shoot.setCharacterSize(fontSize);
	shoot.setFillColor(sf::Color::Green);
	shoot.setOutlineColor(sf::Color::Black);
	shoot.setOutlineThickness(2);
	shoot.setString(tutorialText);

	fileIn.close();

	fileIn.open("files/tutorial_grapple.txt");

	tutorialText = "";

	if (fileIn.is_open())
	{
		while (fileIn.good())
		{
			fileIn >> fileInput;
			if (fileInput == "/")
			{
				tutorialText += "\n";
			}
			else
			{
				tutorialText += fileInput + " ";
			}
		}
		std::cout << tutorialText;
	}
	else
	{
		std::cout << "Error opening tutorial text file: grapple";
	}

	grapple.setFont(font);
	grapple.setCharacterSize(fontSize);
	grapple.setFillColor(sf::Color::Green);
	grapple.setOutlineColor(sf::Color::Black);
	grapple.setOutlineThickness(2);
	grapple.setString(tutorialText);

	fileIn.close();

	fileIn.open("files/tutorial_turret.txt");

	tutorialText = "";

	if (fileIn.is_open())
	{
		while (fileIn.good())
		{
			fileIn >> fileInput;
			if (fileInput == "/")
			{
				tutorialText += "\n";
			}
			else
			{
				tutorialText += fileInput + " ";
			}
		}
		std::cout << tutorialText;
	}
	else
	{
		std::cout << "Error opening tutorial text file: grapple";
	}

	turret.setFont(font);
	turret.setCharacterSize(fontSize);
	turret.setFillColor(sf::Color::Green);
	turret.setOutlineColor(sf::Color::Black);
	turret.setOutlineThickness(2);
	turret.setString(tutorialText);

	fileIn.close();

	fileIn.open("files/tutorial_checkpoint.txt");

	tutorialText = "";

	if (fileIn.is_open())
	{
		while (fileIn.good())
		{
			fileIn >> fileInput;
			if (fileInput == "/")
			{
				tutorialText += "\n";
			}
			else
			{
				tutorialText += fileInput + " ";
			}
		}
		std::cout << tutorialText;
	}
	else
	{
		std::cout << "Error opening tutorial text file: grapple";
	}

	fileIn.close();

	checkpoint.setFont(font);
	checkpoint.setCharacterSize(fontSize);
	checkpoint.setFillColor(sf::Color::Green);
	checkpoint.setOutlineColor(sf::Color::Black);
	checkpoint.setOutlineThickness(2);
	checkpoint.setString(tutorialText);

	// Setting positions of text and adding to vector for easy access
	jump.setPosition(sf::Vector2f(800, 200));
	shoot.setPosition(sf::Vector2f(1750, -250));
	grapple.setPosition(sf::Vector2f(2500, -210));
	turret.setPosition(sf::Vector2f(4500, -210));
	checkpoint.setPosition(sf::Vector2f(3700, -125));

	textVec.push_back(jump);
	textVec.push_back(shoot);
	textVec.push_back(grapple);
	textVec.push_back(turret);
	textVec.push_back(checkpoint);

	// Setting level text that appears in game as "Level (level number)"
	levelText.setFont(font);
	levelText.setCharacterSize(fontSize);
	levelText.setFillColor(sf::Color::Green);
	levelText.setOutlineColor(sf::Color::Black);
	levelText.setOutlineThickness(2);
}

LevelManager::~LevelManager()
{
}

void LevelManager::ChangeLevel(int _index)
{
	for (auto& itr : *levelObjVec)
	{
		delete itr;
		itr = nullptr;
	}
	for (auto& itr : *turretVec)
	{
		delete itr;
		itr = nullptr;
	}
	levelObjVec->clear();
	turretVec->clear();
	grappleVec->clear();

	(*m_levelsCompleted)[_index] = true;

	if (_index == -1)
	{
		m_levelIndex += 1;
	}
	else
	{
		m_levelIndex = _index;
	}

	if (m_levelIndex == 6)
	{
		m_menu->UnlockTrials();
		m_menu->EnableMenu();
		return;
	}

	if (m_levelIndex > *m_currentLevel) { *m_currentLevel = m_levelIndex; }

	switch (m_levelIndex)
	{
	case 1:
		Level1();
		break;
	case 2:
		Level2();
		break;
	case 3:
		Level3();
		break;
	case 4:
		Level4();
		break;
	case 5:
		Level5();
		break;
	}
}

void LevelManager::Level1()
{
	levelText.setString("Level 1\nUse the 'A' and 'D' keys to\nmove left and right!");
	levelText.setPosition(sf::Vector2f(-300, 200));

	player->SetStartPos(b2Vec2(-300, 400));
	//player->SetStartPos(b2Vec2(4000, -100));

	player->SetPosBounds(b2Vec2(-25, -50), b2Vec2(300, 25));

	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(1100, 500),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(2000, 0),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1500, 100),	b2Vec2(300, 500),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(200, 100),	b2Vec2(1250, 500),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 500),	b2Vec2(1300, 300),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(1500, 0),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(2500, 0),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(4000, 100),	b2Vec2(5500, 0),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(3100, -270), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1000, 100),	b2Vec2(5250, -330), world, m_scale));

	grappleVec->push_back(new GrapplePoint(player, b2Vec2(3100, -200), world, m_scale));

	turretVec->push_back(new Turret(player, sf::Vector2f(5000, -250), objVec, 500, 500));
	turretVec->push_back(new Turret(player, sf::Vector2f(5250, -250), objVec, 500, 500));
	turretVec->push_back(new Turret(player, sf::Vector2f(5500, -250), objVec, 500, 500));

	for (auto& itr : *grappleVec)
	{
		levelObjVec->push_back(itr);
	}
}

void LevelManager::Level2()
{
	levelText.setString("Level 2");
	levelText.setPosition(sf::Vector2f(0, 100));

	player->SetStartPos(b2Vec2(300, 400));
	//player->SetStartPos(b2Vec2(500, -600));

	player->SetPosBounds(b2Vec2(-25, -500), b2Vec2(500, 25));

	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(300, 500),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(800, 500),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(1300, 500),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(800, 100),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 500),	b2Vec2(1500, 200),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 500),	b2Vec2(100, -200),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(300, 100),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1000, 100),	b2Vec2(1100, -400), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(2500, -700), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(3250, -650), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1000, 100),	b2Vec2(4250, -300), world, m_scale));

	grappleVec->push_back(new GrapplePoint(player, b2Vec2(2500, -630), world, m_scale));
	grappleVec->push_back(new GrapplePoint(player, b2Vec2(3250, -580), world, m_scale));

	turretVec->push_back(new Turret(player, sf::Vector2f(1000, 180), objVec, 500, 500));

	for (auto& itr : *grappleVec)
	{
		levelObjVec->push_back(itr);
	}
}

void LevelManager::Level3()
{
	levelText.setString("Level 3");
	levelText.setPosition(sf::Vector2f(0, 100));

	player->SetStartPos(b2Vec2(300, 400));

	player->SetPosBounds(b2Vec2(-25, -2000), b2Vec2(500, 25));

	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 1250),	b2Vec2(3200, -625),		world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 1250),	b2Vec2(3400, -625),		world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 1250),	b2Vec2(3100, -625),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 1250),	b2Vec2(3500, -625),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100),	b2Vec2(300, 500),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(1200, 500),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(1800, 500),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(1900, 250),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(1800, 0),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1000, 100),	b2Vec2(3050, 0),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 300),	b2Vec2(3000, -200),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 300),	b2Vec2(3000, -500),		world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 300),	b2Vec2(2600, -500),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 300),	b2Vec2(3000, -800),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 300),	b2Vec2(2600, -800),		world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 300),	b2Vec2(3000, -1100),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 300),	b2Vec2(2600, -1100),	world, m_scale));

	for (auto& itr : *grappleVec)
	{
		levelObjVec->push_back(itr);
	}
}

void LevelManager::Level4()
{
	levelText.setString("Level 4");
	levelText.setPosition(sf::Vector2f(0, 100));

	player->SetStartPos(b2Vec2(0, -600));

	player->SetPosBounds(b2Vec2(-25, -2000), b2Vec2(500, 25));

	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1000, 100),	b2Vec2(0, 100),		world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(400, 100),	b2Vec2(-275, -90),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(450, 100),	b2Vec2(-275, -100), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(400, 100),	b2Vec2(275, -90),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(450, 100),	b2Vec2(275, -100),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(850, 100),	b2Vec2(-50, -290),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(900, 100),	b2Vec2(-50, -300),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(850, 100),	b2Vec2(50, -490),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(900, 100),	b2Vec2(50, -500),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 700),	b2Vec2(550, -200),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 700),	b2Vec2(-550, -200),	world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 1000),	b2Vec2(750, -500),	world, m_scale, true));

	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 1000),	b2Vec2(750, -500),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1200, 100),	b2Vec2(100, 200),	world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100),	b2Vec2(850, -200),	world, m_scale));

	grappleVec->push_back(new GrapplePoint(player, b2Vec2(850, -130), world, m_scale));

	for (auto& itr : *grappleVec)
	{
		levelObjVec->push_back(itr);
	}
}

void LevelManager::Level5()
{
	levelText.setString("Level 5");
	levelText.setPosition(sf::Vector2f(0, 100));

	player->SetStartPos(b2Vec2(0, -2100));

	player->SetPosBounds(b2Vec2(-500, -500), b2Vec2(500, 25));

	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(2000, 100), b2Vec2(0, 100), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(1600, 100), b2Vec2(0, -200), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 500), b2Vec2(0, -500), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 200), b2Vec2(-1050, 50), world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 200), b2Vec2(-1050, -150), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 200), b2Vec2(1050, 50), world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 200), b2Vec2(1050, -150), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100), b2Vec2(-1000, -1500), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(500, 100), b2Vec2(1000, -1500), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(250, 100), b2Vec2(0, -1500), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(2000, 100), b2Vec2(0, -2000), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 500), b2Vec2(-1200, -1800), world, m_scale));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 500), b2Vec2(1200, -1800), world, m_scale));
	//

	for (int i = 0; i < 4; i++)
	{
		levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100), b2Vec2(100, -2150 - i * 200), world, m_scale));
		levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100), b2Vec2(-100, -2150 - i * 200), world, m_scale, true));
		levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100), b2Vec2(100, -2250 - i * 200), world, m_scale, true));
		levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100), b2Vec2(-100, -2250 - i * 200), world, m_scale));
	}
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100), b2Vec2(100, -2950), world, m_scale, true));
	levelObjVec->push_back(new LevelObstacle(sf::Vector2f(100, 100), b2Vec2(-100, -2950), world, m_scale, true));

	turretVec->push_back(new Turret(player, sf::Vector2f(300, -120), objVec, 500, 500));
	turretVec->push_back(new Turret(player, sf::Vector2f(350, -120), objVec, 500, 500));
	turretVec->push_back(new Turret(player, sf::Vector2f(400, -120), objVec, 500, 500));

	turretVec->push_back(new Turret(player, sf::Vector2f(-300, -120), objVec, 500, 500));
	turretVec->push_back(new Turret(player, sf::Vector2f(-350, -120), objVec, 500, 500));
	turretVec->push_back(new Turret(player, sf::Vector2f(-400, -120), objVec, 500, 500));

	grappleVec->push_back(new GrapplePoint(player, b2Vec2(3100, -200), world, m_scale));

	for (auto& itr : *grappleVec)
	{
		levelObjVec->push_back(itr);
	}
}
