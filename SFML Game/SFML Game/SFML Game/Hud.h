#include <SFML/Graphics.hpp>

#pragma once

class Hud 
{
private:
	// Font and text
	sf::Font* font;

	sf::Text* m_health;
	sf::Text* m_currentLevel;

	// Value for font size
	int m_fontSize;

public:
	// Vector for easy access
	std::vector<sf::Drawable*> hudObjects;
	std::vector<sf::Drawable*>::iterator itHud;

	// Methods
	void Draw(sf::RenderWindow* _window);
	void UpdateHud(int _level);

	Hud();
	~Hud();
};