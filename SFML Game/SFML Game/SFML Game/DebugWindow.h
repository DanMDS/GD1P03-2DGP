#include <SFML/Graphics.hpp>

#pragma once

class DebugWindow
{
private:
	// Buttons, text and font
	sf::Font* font;

	sf::Text* m_debugText;
	sf::Text* m_valueSelected;
	sf::Text* m_values;

	sf::RectangleShape* m_buttonColliders;
	sf::RectangleShape* m_buttonControls;
	sf::RectangleShape* m_buttonSpawnEnemy;
	sf::RectangleShape* m_buttonShootingEnemy;
	sf::RectangleShape* m_buttonValueChanging;

	// Background for easy colour changing
	sf::RectangleShape* m_background;

	// Methods for button presses
	void ToggleDebugControls();
	void ToggleColliders();
	void ToggleEnemySpawn();
	void ToggleEnemyShoot();
	void ToggleValueChanging();

	// int for font size
	int m_fontSize;

public:
	// Int for selection arrow
	int m_valueSelectedYPos;

	// Vectors for easy button access
	std::vector<sf::Drawable*> debugObjects;
	std::vector<sf::Drawable*>::iterator itButtons;

	// Bools easy access
	bool m_showColliders;
	bool m_debugControls;
	bool m_spawnEnemy;
	bool m_shootingEnemy;
	bool m_valueChanging;

	// Methods
	void Update(sf::RenderWindow* _window, sf::Vector2f _mousePos, bool _mousePressed, int _playerShootDelay, int _playerSpeed, int _playerShootSpeed);

	void Draw(sf::RenderWindow* _window);

	DebugWindow();
	~DebugWindow();
};