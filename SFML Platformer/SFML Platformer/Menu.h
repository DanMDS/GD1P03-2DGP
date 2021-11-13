#include <SFML/Graphics.hpp>

#pragma once

class Menu
{
private:
	sf::Font font;
	sf::Text menuMain[5];
	sf::Text menuLevelSelect[5];
	sf::Text menuOptions[4];

	sf::Image* lockImage;
	sf::Texture* lockTexture;
	sf::Sprite* lockSprite;

	sf::Texture* m_starTexture;
	sf::Sprite* m_starSprite;

	sf::RectangleShape* trans;

	sf::RenderWindow* window;

	sf::Vector2i mousePos;
	sf::Vector2f viewCenter;
	sf::View* view;

	bool inMenu;
	bool mouseDown;
	bool (*m_levelsCompleted)[5];
	bool m_timeTrialsUnlocked;
	bool m_timeTrialsActive;
	bool (*m_timeTrialComplete)[5];

	int fontSize;

	int xPos;
	int yPos;
	int itemInc;
	int index;
	int* m_currentLevel;

	float windowSpeed;

	enum class CurrentMenu
	{
		Main,
		Trials,
		LevelSelect,
		Options
	};

	CurrentMenu currentMenu;

public:
	Menu(sf::RenderWindow* _window, 
		bool _timeTrials, 
		sf::View* _view, 
		bool(*_levelsCompleted)[5],
		bool(*_timeTrialComplete)[5],
		int* _currentLevel);
	~Menu();

	void MoveWindow(sf::Vector2f _pos);
	void Update();
	void Main();
	void Play(int _index);
	void Trials();
	void LevelSelect();
	void Options();
	void Exit();
	void Draw();

	void EnableMenu()					{ inMenu = true;						};
	void UnlockTrials()					{ m_timeTrialsUnlocked = true;			};
	void SetTrialComplete(int _index)	{ (*m_timeTrialComplete)[_index] = true;	}

	bool InMenu()						{ return inMenu;						};
	bool TimeTrialsActive()				{ return m_timeTrialsActive;			};

	int RunMenu();
};