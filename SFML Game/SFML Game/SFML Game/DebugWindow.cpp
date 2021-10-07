#include <iostream>
#include "DebugWIndow.h"

void DebugWindow::CheckButtons(sf::RenderWindow* _window, sf::Vector2f _mousePos)
{
	if (m_buttonColliders->getGlobalBounds().contains(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window))))
	{
		ToggleColliders();
	}
}

void DebugWindow::ToggleColliders()
{
	m_showColliders = !m_showColliders;
}

void DebugWindow::Draw(sf::RenderWindow* _window)
{
	for (itButtons = shapes.begin(); itButtons != shapes.end(); itButtons++)
	{
		_window->draw(*(*itButtons));
	}
}

DebugWindow::DebugWindow()
{
	// Creating buttons and background
	m_background = new sf::RectangleShape(sf::Vector2f(500, 500));
	m_background->setFillColor(sf::Color::White);
	shapes.push_back(m_background);

	m_buttonColliders = new sf::RectangleShape(sf::Vector2f(50, 50));
	m_buttonColliders->setFillColor(sf::Color::Blue);
	shapes.push_back(m_buttonColliders);
}

DebugWindow::~DebugWindow()
{
	for (itButtons = shapes.begin(); itButtons != shapes.end(); itButtons++)
	{
		sf::RectangleShape* temp = *itButtons;
		delete temp;
		temp = nullptr;
	}
	shapes.clear();
}
