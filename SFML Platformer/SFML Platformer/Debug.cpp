#include <iostream>
#include "Debug.h"

Debug::Debug(Player* _player, int* _turretShootCooldown, int* _turretAlertDist, int* _playerShoot, int* _rocketSpeed)
{
	m_windowD = new sf::RenderWindow(sf::VideoMode(500, 500), "Debug", sf::Style::Close);
	m_windowD->setFramerateLimit(60);
	m_windowD->setVisible(false);
	m_windowOpen = false;

	m_player = _player;
	m_turretShootCooldown = _turretShootCooldown;
	m_turretAlertDist = _turretAlertDist;
	m_playerShoot = _playerShoot;
	m_rocketSpeed = _rocketSpeed;

	m_mousePos = sf::Vector2f(0, 0);

	if (!m_font.loadFromFile("ARIAL.ttf"))
	{
		std::cout << "Error loading font";
	}

	m_fileIn.open("files/values.ini");
	if (!m_fileIn.is_open())
	{
		std::cout << "Error opening debug file\n";
	}

	m_input = 0;

	// Creating menu buttons
	m_fileIn >> m_input;
	m_buttonVec.push_back(new OptionButton(sf::Vector2f(-50, 50), m_font, m_input, 50, 100, 1000, "Player Shoot Cooldown: ", 1));

	m_fileIn.ignore(100, '\n');
	m_fileIn >> m_input;
	m_buttonVec.push_back(new OptionButton(sf::Vector2f(-50, 100), m_font, m_input, 5, 5, 100, "Player Max Speed: ", 2));

	m_fileIn.ignore(100, '\n');
	m_fileIn >> m_input;
	m_buttonVec.push_back(new OptionButton(sf::Vector2f(-50, 100), m_font, m_input, 5, 5, 100, "Player Acceleration: ", 3));

	m_fileIn.ignore(100, '\n');
	m_fileIn >> m_input;
	m_buttonVec.push_back(new OptionButton(sf::Vector2f(-50, 150), m_font, m_input, 50, 100, 1000, "Turret Shoot Cooldown: ", 4));

	m_fileIn.ignore(100, '\n');
	m_fileIn >> m_input;
	m_buttonVec.push_back(new OptionButton(sf::Vector2f(-50, 200), m_font, m_input, 50, 100, 1000, "Turret Alert Distance: ", 5));

	m_fileIn.ignore(100, '\n');
	m_fileIn >> m_input;
	m_buttonVec.push_back(new OptionButton(sf::Vector2f(-50, 250), m_font, m_input, 1, 1, 10, "Rocket Speed: ", 6));

	m_fileIn.close();

	// Setting variables 
	*m_playerShoot = *m_buttonVec[0]->GetValue();
	m_player->SetMaxSpeed(*m_buttonVec[1]->GetValue());
	m_player->SetAcceleration(*m_buttonVec[2]->GetValue());
	*m_turretShootCooldown = *m_buttonVec[3]->GetValue();
	*m_turretAlertDist = *m_buttonVec[4]->GetValue();
	*m_rocketSpeed = *m_buttonVec[5]->GetValue();
}

Debug::~Debug()
{
	m_fileOut.open("files/values.ini");
	if (!m_fileOut.is_open())
	{
		std::cout << "Error opening debug file\n";
	}
	else
	{
		m_fileOut << *m_buttonVec[0]->GetValue() << "// Player Shoot Cooldown\n";
		m_fileOut << *m_buttonVec[1]->GetValue() << "// Player Max Speed\n";
		m_fileOut << *m_buttonVec[2]->GetValue() << "// Player Acceleration\n";
		m_fileOut << *m_buttonVec[3]->GetValue() << "// Turret Shoot Cooldown\n";
		m_fileOut << *m_buttonVec[4]->GetValue() << "// Turret Alert Distance\n";
		m_fileOut << *m_buttonVec[5]->GetValue() << "// Rocket Speed\n";
	}

	m_fileOut.close();

	for (auto itr : m_buttonVec)
	{
		delete itr;
		itr = nullptr;
	}
	m_buttonVec.clear();
}

void Debug::OpenWindow()
{
	m_windowD->setVisible(true);
	m_windowOpen = true;

	while (m_windowOpen)
	{
		m_mousePos = m_windowD->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*m_windowD)));

		sf::Event event;
		while (m_windowD->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_windowOpen = false;
				m_windowD->setVisible(false);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					CheckButtons();
				}
			}
		}

		m_windowD->clear(sf::Color::White);

		for (auto itr : m_buttonVec)
		{
			itr->Draw(m_windowD);
		}

		m_windowD->display();
	}
}

void Debug::CheckButtons()
{
	*m_playerShoot = *m_buttonVec[0]->CheckButton(m_mousePos);

	m_player->SetMaxSpeed(*m_buttonVec[1]->CheckButton(m_mousePos));
	m_player->SetAcceleration(*m_buttonVec[2]->CheckButton(m_mousePos));

	*m_turretShootCooldown = *m_buttonVec[3]->CheckButton(m_mousePos);
	*m_turretAlertDist = *m_buttonVec[4]->CheckButton(m_mousePos);

	*m_rocketSpeed = *m_buttonVec[5]->CheckButton(m_mousePos);
}
