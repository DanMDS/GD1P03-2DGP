#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"
#include "Interactable.h"

#pragma once

class Level
{
private:
	// Sprite and textures
	sf::Sprite* m_levelCanvasSprite;
	sf::Texture* m_levelCanvasTitle;
	sf::Texture* m_levelCanvasTutorial;
	sf::Texture* m_levelCanvasTexture1;
	sf::Texture* m_levelCanvasTexture2;
	sf::Texture* m_levelCanvasTexture3;
	sf::Texture* m_levelCanvasTextureDeath;

	// Level size
	sf::Vector2f m_levelDimensions;

	// Int for completed level count
	int m_levelsCompleted;

	// Collider object
	Collider* m_levelCol;

	// Ints for random background calculations
	int m_levelBg;
	int m_levelTemp;

	// Int for random level selection and object placing
	int m_levelIndex;

	// Player start position
	const sf::Vector2f m_playerSpawnPoint = sf::Vector2f(100, 360);

public:
	// Methods
	void ChangeLevel(Player* _player, std::vector<Enemy*> _enemies, int _index = 0);
	bool LevelEndCheck(int _enemiesRemaining, std::vector<Interactable*> _interacts);

	// Draws level sprite
	void Draw(sf::RenderWindow* _window)		{ _window->draw(*m_levelCanvasSprite);	};
	
	// Getters
	Collider* GetCollider()						{ return m_levelCol;					};
	int GetLevelIndex()							{ return m_levelIndex;					};
	const sf::Vector2f GetPlayerSpawnPoint()	{ return m_playerSpawnPoint;			};

	Level(sf::String _spritePath);
	~Level();
};