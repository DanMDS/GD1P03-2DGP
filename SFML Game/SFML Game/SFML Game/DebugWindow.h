#include <SFML/Graphics.hpp>

#pragma once

class DebugWindow
{
private:
	sf::RectangleShape* m_buttonColliders;
	sf::RectangleShape* m_background;

public:
	std::vector<sf::RectangleShape*> shapes;
	std::vector<sf::RectangleShape*>::iterator itButtons;

	bool m_showColliders = false;

	void CheckButtons(sf::RenderWindow* _window, sf::Vector2f _mousePos);
	void ToggleColliders();

	void Draw(sf::RenderWindow* _window);

	DebugWindow();
	~DebugWindow();
};