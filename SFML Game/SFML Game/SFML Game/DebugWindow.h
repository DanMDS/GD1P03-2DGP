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

	// int for font size
	int m_fontSize;

	// Bools for easy access
	bool m_showColliders;
	bool m_debugControls;
	bool m_spawnEnemy;
	bool m_shootingEnemy;
	bool m_valueChanging;

	// Int for selection arrow
	int m_valueSelectedYPos;

public:

	// Vectors for easy button access
	std::vector<sf::Drawable*> debugObjects;
	std::vector<sf::Drawable*>::iterator itButtons;

	// Set position for value selection
	void SetValueSelectedPos(int _num)	{ m_valueSelectedYPos = _num;			};

	// Get functions for button booleans for manager decisions
	int GetValueSelectedPos()			{ return m_valueSelectedYPos;			};
	bool GetShowColliders()				{ return m_showColliders;				};
	bool GetDebugControls()				{ return m_debugControls;				};
	bool GetSpawnEnemy()				{ return m_spawnEnemy;					};
	bool GetShootingEnemy()				{ return m_shootingEnemy;				};
	bool GetValueChanging()				{ return m_valueChanging;				};

	// Update, draw and contructor/destructor methods
	void Update(sf::RenderWindow* _window, sf::Vector2f _mousePos, bool _mousePressed, int _playerShootDelay, int _playerSpeed, int _playerShootSpeed);

	void Draw(sf::RenderWindow* _window);

	DebugWindow();
	~DebugWindow();
};