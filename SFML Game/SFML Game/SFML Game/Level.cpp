#include <iostream>
#include <string>
#include "Level.h"

void Level::ChangeLevel()
{
	levelIndex = rand() % 10 + 1;

	levelName = "levels/level " + std::to_string(levelIndex) + ".png";

	if (!levelCanvasTexture.loadFromFile(levelName))
	{
		std::cout << "Error: Loading level 1 image";
	}

	levelCanvasSprite.setTexture(levelCanvasTexture);
}

void Level::Draw(sf::RenderWindow* _window)
{
	_window->draw(levelCanvasSprite);
}

bool Level::LevelEndCheck(sf::Vector2f _playerPos, int _enemiesRemaining)
{
	if (_enemiesRemaining == 0)
	{
		return true;
	}
	return false;
}

Level::Level(sf::String _spritePath)
{
	levelIndex = 0;
	levelName = "levels/level " + std::to_string(levelIndex) = ".png";

	if (!levelCanvasTexture.loadFromFile(_spritePath))
	{
		std::cout << "Error: Loading level 1 image";
	}

	levelCanvasSprite.setTexture(levelCanvasTexture);
}

Level::~Level()
{

}
