#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"
#include "Interactable.h"

#pragma once

class Level
{
private:
	sf::Sprite levelCanvasSprite;

	sf::Texture levelCanvasTitle;

	sf::Texture levelCanvasTexture1;

	sf::Texture levelCanvasTexture2;

	sf::Texture levelCanvasTexture3;

	sf::Texture levelCanvasTextureDeath;

	sf::Vector2f levelDimensions;

	std::string levelName;
	int levelsCompleted;

	Collider* levelCol;

	int levelBg;
	int levelTemp;

public:
	int levelIndex;

	const sf::Vector2f playerSpawnPoint = sf::Vector2f(100, 360);
	void ChangeLevel(Player* _player, std::vector<Enemy*> _enemies, int _index = 0);

	void Draw(sf::RenderWindow* _window);
	bool LevelEndCheck(int _enemiesRemaining, std::vector<Interactable*> _interacts);

	Collider* GetCollider();

	Level(sf::String _spritePath);
	~Level();
};