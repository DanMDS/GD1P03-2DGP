#include "Hud.h"
#include <string>

void Hud::Draw(sf::RenderWindow* _window)
{
	// Drawing objects
	for (auto& itr : hudObjects)
	{
		_window->draw(*itr);
	}
}

void Hud::UpdateHud(int _level)
{
	// Updating level counter
	m_currentLevel->setString("Level: " + std::to_string(_level));
}

Hud::Hud()
{
	// Initialising variable and loading fonts and text
	m_fontSize = 25;

	font = new sf::Font();
	font->loadFromFile("fonts/AltoneTrial-Regular.ttf");

	m_health = new sf::Text("Health:", *font, m_fontSize);
	m_health->setFillColor(sf::Color::White);
	m_health->setOutlineColor(sf::Color::Black);
	m_health->setOutlineThickness(2);
	m_health->setPosition(50, 2.5);
	hudObjects.push_back(m_health);

	m_currentLevel = new sf::Text("Level:", *font, m_fontSize);
	m_currentLevel->setFillColor(sf::Color::White);
	m_currentLevel->setOutlineColor(sf::Color::Black);
	m_currentLevel->setOutlineThickness(2);
	m_currentLevel->setPosition(350, 2.5);
	hudObjects.push_back(m_currentLevel);
}

Hud::~Hud()
{
	// Deallocating memory
	delete m_health, m_currentLevel, font;
	m_health = nullptr;
	m_currentLevel = nullptr;
	font = nullptr;
}
