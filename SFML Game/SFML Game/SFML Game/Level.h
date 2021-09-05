#include <SFML/Graphics.hpp>

#pragma once

class Level
{
private:
	sf::Image* levelCanvasImage;
	sf::Texture levelCanvasTexture;
	sf::Sprite levelCanvasSprite;

	sf::Vector2f levelDimensions;

	std::string levelName;
	int levelIndex;

public:
	void ChangeLevel();

	void Draw(sf::RenderWindow* _window);
	bool LevelEndCheck(sf::Vector2f _playerPos, int _enemiesRemaining);

	Level(sf::String _spritePath);
	~Level();
};