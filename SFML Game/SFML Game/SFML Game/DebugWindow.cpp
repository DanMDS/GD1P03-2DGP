#include "DebugWindow.h"

/*
	Function: Update()
	Returns: void
	Parameters: sf::RenderWindow* _window, 
		sf::Vector2f _mousePos, 
		bool _mousePressed, 
		int _playerShootDelay, 
		int _playerSpeed, 
		int _playerShootSpeed
	Summary: Updates booleans for each button when pressed, and in turn their fill colours to indicate state
*/
void DebugWindow::Update(sf::RenderWindow* _window, sf::Vector2f _mousePos, bool _mousePressed, int _playerShootDelay, int _playerSpeed, int _playerShootSpeed)
{
	// Checking when buttons are pressed and running functions
	if (_mousePressed)
	{
		if (m_buttonColliders->getGlobalBounds().contains(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window))))
		{
			m_showColliders = !m_showColliders;
		}
		if (m_buttonControls->getGlobalBounds().contains(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window))))
		{
			m_debugControls = !m_debugControls;
		}
		if (m_buttonSpawnEnemy->getGlobalBounds().contains(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window))))
		{
			m_spawnEnemy = !m_spawnEnemy;
		}
		if (m_buttonShootingEnemy->getGlobalBounds().contains(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window))))
		{
			m_shootingEnemy = !m_shootingEnemy;
		}
		if (m_buttonValueChanging->getGlobalBounds().contains(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window))))
		{
			m_valueChanging = !m_valueChanging;
		}
	}

	if (m_showColliders)
	{
		m_buttonColliders->setFillColor(sf::Color::Blue);
	}
	else
	{
		m_buttonColliders->setFillColor(sf::Color::White);
	}

	if (m_debugControls)
	{
		m_buttonControls->setFillColor(sf::Color::Blue);
	}
	else
	{
		m_buttonControls->setFillColor(sf::Color::White);
	}

	if (m_spawnEnemy)
	{
		m_buttonSpawnEnemy->setFillColor(sf::Color::Blue);
	}
	else
	{
		m_buttonSpawnEnemy->setFillColor(sf::Color::White);
	}

	if (m_shootingEnemy)
	{
		m_buttonShootingEnemy->setFillColor(sf::Color::Blue);
	}
	else
	{
		m_buttonShootingEnemy->setFillColor(sf::Color::White);
	}

	if (m_valueChanging)
	{
		m_buttonValueChanging->setFillColor(sf::Color::Blue);
	}
	else
	{
		m_buttonValueChanging->setFillColor(sf::Color::White);
	}

	m_valueSelected->setPosition(350, float(m_valueSelectedYPos));

	m_values->setString(std::to_string(_playerShootDelay) + "\n" + std::to_string(_playerSpeed) + "\n" + std::to_string(_playerShootSpeed));
}

/*
	Function: Draw()
	Returns: void
	Parametres: sf::RenderWindow* _window
	Summary: Draws all of the objects in the debugObjects vector (all text and buttons)
*/
void DebugWindow::Draw(sf::RenderWindow* _window)
{
	for (auto& itr : debugObjects)
	{
		_window->draw(*itr);
	}
}

DebugWindow::DebugWindow()
{
	// Initialising variables
	m_debugControls = false;
	m_showColliders = false;
	m_spawnEnemy = false;
	m_shootingEnemy = false;
	m_valueChanging = false;

	m_fontSize = 25;

	font = new sf::Font();
	font->loadFromFile("fonts/AltoneTrial-Regular.ttf");

	// Creating buttons and background
	m_background = new sf::RectangleShape(sf::Vector2f(500, 500));
	m_background->setFillColor(sf::Color::White);
	debugObjects.push_back(m_background);

	// Show colliders
	m_buttonColliders = new sf::RectangleShape(sf::Vector2f(25, 25));
	m_buttonColliders->setFillColor(sf::Color::White);
	m_buttonColliders->setOutlineColor(sf::Color::Black);
	m_buttonColliders->setOutlineThickness(2);
	m_buttonColliders->setPosition(470, 5);
	debugObjects.push_back(m_buttonColliders);

	// Enable debug controls
	m_buttonControls = new sf::RectangleShape(sf::Vector2f(25, 25));
	m_buttonControls->setFillColor(sf::Color::White);
	m_buttonControls->setOutlineColor(sf::Color::Black);
	m_buttonControls->setOutlineThickness(2);
	m_buttonControls->setPosition(470, 35);
	debugObjects.push_back(m_buttonControls);

	// Spawn enemy on right click
	m_buttonSpawnEnemy = new sf::RectangleShape(sf::Vector2f(25, 25));
	m_buttonSpawnEnemy->setFillColor(sf::Color::White);
	m_buttonSpawnEnemy->setOutlineColor(sf::Color::Black);
	m_buttonSpawnEnemy->setOutlineThickness(2);
	m_buttonSpawnEnemy->setPosition(470, 65);
	debugObjects.push_back(m_buttonSpawnEnemy);

	// ^ Spawn shooting enemy
	m_buttonShootingEnemy = new sf::RectangleShape(sf::Vector2f(25, 25));
	m_buttonShootingEnemy->setFillColor(sf::Color::White);
	m_buttonShootingEnemy->setOutlineColor(sf::Color::Black);
	m_buttonShootingEnemy->setOutlineThickness(2);
	m_buttonShootingEnemy->setPosition(470, 95);
	debugObjects.push_back(m_buttonShootingEnemy);

	// Enable value changing
	m_buttonValueChanging = new sf::RectangleShape(sf::Vector2f(25, 25));
	m_buttonValueChanging->setFillColor(sf::Color::White);
	m_buttonValueChanging->setOutlineColor(sf::Color::Black);
	m_buttonValueChanging->setOutlineThickness(2);
	m_buttonValueChanging->setPosition(470, 125);
	debugObjects.push_back(m_buttonValueChanging);
	
	// Displaying debug values such as player speed, player shoot cooldown, etc
	m_debugText = new sf::Text("Show colliders:\nEnable debug controls:\nSpawn enemy on right click:\n    - Shooting enemy:\nEnable value changing:\n\n\n\nDebug Values\n(Space bar to cycle values, up/down\narrow keys to edit)\nPlayer shoot cooldown:\nPlayer speed:\nPlayer bullet speed:\n", *font, m_fontSize);
	m_debugText->setFillColor(sf::Color::Black);
	debugObjects.push_back(m_debugText);

	m_valueSelectedYPos = 330;

	m_valueSelected = new sf::Text("<-", *font, 25);
	m_valueSelected->setFillColor(sf::Color::Black);
	m_valueSelected->setPosition(350, float(m_valueSelectedYPos));
	debugObjects.push_back(m_valueSelected);

	m_values = new sf::Text("", *font, 25);
	m_values->setFillColor(sf::Color::Black);
	m_values->setPosition(400, 330);
	debugObjects.push_back(m_values);
}

DebugWindow::~DebugWindow()
{
	delete font;
	font = nullptr;
	// Deallocating memory
	for (auto& itr : debugObjects)
	{
		delete itr;
		itr = nullptr;
	}
	debugObjects.clear();
}