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
	sf::Sprite* levelCanvasSprite;
	sf::Texture* levelCanvasTitle;
	sf::Texture* levelCanvasTutorial;
	sf::Texture* levelCanvasTexture1;
	sf::Texture* levelCanvasTexture2;
	sf::Texture* levelCanvasTexture3;
	sf::Texture* levelCanvasTextureDeath;

	// Level size
	sf::Vector2f levelDimensions;

	// Int for completed level count
	int levelsCompleted;

	// Collider object
	Collider* levelCol;

	// Ints for random background calculations
	int levelBg;
	int levelTemp;

public:
	// Int for random level selection and object placing
	int levelIndex;

	// Player start position
	const sf::Vector2f playerSpawnPoint = sf::Vector2f(100, 360);

	// Methods
	void ChangeLevel(Player* _player, std::vector<Enemy*> _enemies, int _index = 0);

	void Draw(sf::RenderWindow* _window);
	bool LevelEndCheck(int _enemiesRemaining, std::vector<Interactable*> _interacts);

	Collider* GetCollider();

	Level(sf::String _spritePath);
	~Level();
};