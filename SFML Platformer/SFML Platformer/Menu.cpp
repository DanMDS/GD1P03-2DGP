#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow* _window, bool _timeTrialsUnlocked, sf::View* _view, bool (*_levelsCompleted)[5], bool(*_timeTrialComplete)[5], int* _currentLevel)
{
	currentMenu = CurrentMenu::Main;

	m_currentLevel = _currentLevel;

	m_timeTrialsActive = false;

	m_timeTrialComplete = _timeTrialComplete;

	mouseDown = false;

	index = 0;

	m_levelsCompleted = _levelsCompleted;

	window = _window;
	view = _view;
	viewCenter = _window->getView().getCenter();
	inMenu = true;
	windowSpeed = 20;

	trans = new sf::RectangleShape(sf::Vector2f(float(_window->getSize().x), float(_window->getSize().x)));

	trans->setPosition(sf::Vector2f(500, 1500));
	trans->setFillColor(sf::Color(0, 255, 0, 0));
	trans->setOrigin(sf::Vector2f(trans->getGlobalBounds().width / 2, trans->getGlobalBounds().height / 2));

	m_timeTrialsUnlocked = _timeTrialsUnlocked;
	
	if (!font.loadFromFile("ARIAL.ttf"))
	{
		printf("Error loading font");
	}

	m_starTexture = new sf::Texture();
	m_starSprite = new sf::Sprite();

	if (!m_starTexture->loadFromFile("sprites/star.png"))
	{
		std::cout << "Error loading star image";
	}
	m_starSprite->setTexture(*m_starTexture);
	m_starSprite->setOrigin(sf::Vector2f(0, m_starSprite->getGlobalBounds().height / 2));
	
	lockImage = new sf::Image();
	lockImage = new sf::Image();
	lockTexture = new sf::Texture();
	lockSprite = new sf::Sprite();

	if (!lockImage->loadFromFile("sprites/lock.png"))
	{
		printf("Error loading lock image");
	}
	lockImage->createMaskFromColor(sf::Color::Blue);
	lockTexture->loadFromImage(*lockImage);
	lockSprite->setTexture(*lockTexture);
	
	fontSize = 50;

	itemInc = fontSize * 2;

	xPos = _window->getSize().x / 2;
	yPos = 250;

	menuMain[0].setString("Play");
	menuMain[1].setString("Time Trials");
	menuMain[2].setString("Level Select");
	menuMain[3].setString("Options");
	menuMain[4].setString("Exit");

	menuLevelSelect[0].setString("Level 1");
	menuLevelSelect[1].setString("Level 2");
	menuLevelSelect[2].setString("Level 3");
	menuLevelSelect[3].setString("Level 4");
	menuLevelSelect[4].setString("Level 5");
	
	for (int i = 0; i < 5; i++)
	{
		menuMain[i].setFont(font);
		menuMain[i].setCharacterSize(fontSize);
		menuMain[i].setFillColor(sf::Color::Black);
		menuMain[i].setOutlineColor(sf::Color::Black);
		menuMain[i].setOutlineThickness(1);
		menuMain[i].setPosition(sf::Vector2f(xPos - round(menuMain[i].getGlobalBounds().width / 2), float(i * itemInc + yPos)));
	}

	for (int i = 0; i < 5; i++)
	{
		menuLevelSelect[i].setFont(font);
		menuLevelSelect[i].setCharacterSize(fontSize);
		menuLevelSelect[i].setFillColor(sf::Color::Black);
		menuLevelSelect[i].setOutlineColor(sf::Color::Black);
		menuLevelSelect[i].setOutlineThickness(1);
		menuLevelSelect[i].setPosition(sf::Vector2f(-xPos - round(menuLevelSelect[i].getGlobalBounds().width / 2), float(i * itemInc + yPos)));
	}

	lockSprite->setPosition(sf::Vector2f(menuMain[1].getPosition().x + menuMain[1].getGlobalBounds().width + 10,
		menuMain[1].getPosition().y + menuMain[1].getGlobalBounds().height / 2));

	if (!_timeTrialsUnlocked)
	{
		menuMain[1].setFillColor(sf::Color(200, 200, 200));
		menuMain[1].setOutlineColor(sf::Color(200, 200, 200));
	}
}

Menu::~Menu()
{
}

void Menu::Update()
{
	mousePos = sf::Mouse::getPosition(*window);
	switch (currentMenu)
	{
	case CurrentMenu::Main:
		Main();
		break;
	case CurrentMenu::Trials:
		Trials();
		break;
	case CurrentMenu::LevelSelect:
		LevelSelect();
		break;
	case CurrentMenu::Options:
		Options();
		break;
	}
}

void Menu::MoveWindow(sf::Vector2f _pos)
{
	if (viewCenter.x < _pos.x - windowSpeed)
	{
		viewCenter.x += windowSpeed;
	}
	else if (viewCenter.x > _pos.x + windowSpeed)
	{
		viewCenter.x -= windowSpeed;
	}
	else
	{
		viewCenter.x = _pos.x;
	}

	if (viewCenter.y < _pos.y - windowSpeed)
	{
		viewCenter.y += windowSpeed;
	}
	else if (viewCenter.y > _pos.y + windowSpeed)
	{
		viewCenter.y -= windowSpeed;
	}
	else
	{
		viewCenter.y = _pos.y;
	}
	view->setCenter(viewCenter);
	window->setView(*view);
}

void Menu::Main()
{
	MoveWindow(sf::Vector2f(float(window->getSize().x / 2), float(window->getSize().y / 2)));
	for (int i = 0; i < 5; i++)
	{
		if (menuMain[i].getGlobalBounds().contains(sf::Vector2f(float(mousePos.x), float(mousePos.y))))
		{
			menuMain[i].setFillColor(sf::Color::Green);
			if (mouseDown)
			{
				switch (i)
				{
				case 0:
					Play(*m_currentLevel);
					break;
				case 1:
					if (m_timeTrialsUnlocked) { currentMenu = CurrentMenu::Trials; }
					break;
				case 2:
					currentMenu = CurrentMenu::LevelSelect;
					break;
				case 3:
					currentMenu = CurrentMenu::Options;
					break;
				case 4:
					Exit();
					break;
				}
			}
		}
		else
		{
			menuMain[i].setFillColor(sf::Color::Black);
		}
	}
	if (!m_timeTrialsUnlocked)
	{
		menuMain[1].setFillColor(sf::Color(200, 200, 200));
	}
}

void Menu::Play(int _index)
{
	index =_index;
	inMenu = false;
}

void Menu::Trials()
{
	MoveWindow(sf::Vector2f(float(window->getSize().x / 2 + window->getSize().x), float(window->getSize().y / 2)));
}

void Menu::LevelSelect()
{
	MoveWindow(sf::Vector2f(float(int(window->getSize().x / 2) - int(window->getSize().x)), float(window->getSize().y / 2)));
	// Checking if menu buttons have been pressed or hovered over, changing colours and running levels accordingly
	for (int i = 0; i < 5; i++)
	{
		if ((*m_levelsCompleted)[i])
		{
			if (menuLevelSelect[i].getGlobalBounds().contains(sf::Vector2f(float(mousePos.x - int(window->getSize().x)), float(mousePos.y))))
			{
				menuLevelSelect[i].setFillColor(sf::Color::Green);
				if (mouseDown)
				{
					switch (i)
					{
					case 0:
						Play(1);
						break;
					case 1:
						Play(2);
						break;
					case 2:
						Play(3);
						break;
					case 3:
						Play(4);
						break;
					case 4:
						Play(5);
						break;
					}
				}
			}
			else
			{
				menuLevelSelect[i].setFillColor(sf::Color::Black);
			}
		}
		else
		{
			menuLevelSelect[i].setFillColor(sf::Color(200, 200, 200));
		}
	}
}

void Menu::Options()
{
	MoveWindow(sf::Vector2f(float(window->getSize().x / 2), float(window->getSize().y / 2 + window->getSize().y)));
}

void Menu::Exit()
{
	window->close();
}

void Menu::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		if (!(*m_levelsCompleted)[i])
		{
			lockSprite->setPosition(sf::Vector2f(menuLevelSelect[i].getPosition().x + menuLevelSelect[i].getGlobalBounds().width + 10,
				menuLevelSelect[i].getPosition().y + menuLevelSelect[i].getGlobalBounds().height / 2));
			window->draw(*lockSprite);
		}

		if ((*m_timeTrialComplete)[i])
		{
			m_starSprite->setPosition(sf::Vector2f(menuLevelSelect[i].getPosition().x + menuLevelSelect[i].getGlobalBounds().width + 10,
				menuLevelSelect[i].getPosition().y + menuLevelSelect[i].getGlobalBounds().height / 2));
			window->draw(*m_starSprite);
		}
	}

	for (auto itr : menuMain)
	{
		window->draw(itr);
	}
	for (auto itr : menuLevelSelect)
	{
		window->draw(itr);
	}
	lockSprite->setPosition(sf::Vector2f(menuMain[1].getPosition().x + menuMain[1].getGlobalBounds().width + 10,
		menuMain[1].getPosition().y + menuMain[1].getGlobalBounds().height / 2));
	if (!m_timeTrialsUnlocked) { window->draw(*lockSprite); }
}

int Menu::RunMenu()
{
	inMenu = true;
	trans->setFillColor(sf::Color(trans->getFillColor().r,
		trans->getFillColor().g,
		trans->getFillColor().b,
		0));
	currentMenu = CurrentMenu::Main; 
	viewCenter = sf::Vector2f(float(window->getSize().x / 2), float(window->getSize().y / 2));
	view->setCenter(viewCenter);
	window->setView(*view);

	menuMain[1].setOutlineColor(m_timeTrialsUnlocked ? sf::Color::Black : sf::Color(200, 200, 200));

	while (window->isOpen() && inMenu)
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
					mouseDown = true;
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					currentMenu = CurrentMenu::Main;
				}
			}
		}

		Update();

		window->clear(sf::Color::Cyan);
		Draw();
		window->display();

		mouseDown = false;
	}

	trans->setPosition(view->getCenter());

	while (trans->getFillColor().a < 249)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}
		trans->setFillColor(sf::Color(trans->getFillColor().r, 
			trans->getFillColor().g, 
			trans->getFillColor().b, 
			trans->getFillColor().a + 10));

		window->clear(sf::Color::Cyan);
		Draw();
		window->draw(*trans);
		window->display();
	}

	return index;
}