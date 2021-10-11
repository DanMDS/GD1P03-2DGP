#include <iostream>
#include <string>
#include "Level.h"

void Level::ChangeLevel(Player* _player, std::vector<Enemy*> _enemies, int _index)
{
	// Randomizing level or setting to a specific one depending on _index, setting texture accordingly
	if (_index == -4)
	{
		levelTemp = levelIndex;
		while (levelIndex == levelTemp)
		{
			levelIndex = rand() % 10;
		}
		std::cout << levelIndex;

		levelTemp = levelBg;
		while (levelBg == levelTemp || levelBg < 0)
		{
			levelBg = rand() % 3;
		}
	}
	else
	{
		levelIndex = _index;
		switch (levelIndex)
		{
		case -3:
			levelBg = -3;

			break;
		case -2:
			levelBg = -2;
			break;

		case -1:
			levelBg = -1;

			break;
		}
	}

	switch (levelBg)
	{
	case -3:
		levelCanvasSprite->setTexture(*levelCanvasTitle);
		break;
	case -2:
		levelCanvasSprite->setTexture(*levelCanvasTutorial);
		break;
	case -1:
		levelCanvasSprite->setTexture(*levelCanvasTextureDeath);
		break;
	case 0:
		levelCanvasSprite->setTexture(*levelCanvasTexture1);
		break;
	case 1:
		levelCanvasSprite->setTexture(*levelCanvasTexture2);
		break;
	case 2:
		levelCanvasSprite->setTexture(*levelCanvasTexture3);
		break;
	}

	// Moving and scaling obstacles based on level index
	levelCol->UpdateColliders(&levelIndex);

	// Resetting player position
	_player->SetPlayerPosition(playerSpawnPoint);
}

void Level::Draw(sf::RenderWindow* _window)
{
	// Drawing level
	_window->draw(*levelCanvasSprite);
}

bool Level::LevelEndCheck(int _enemiesRemaining, std::vector<Interactable*> _interacts)
{
	// Checking if the level can be ended
	if (_enemiesRemaining != 0)
	{
		return false;
	}

	for (auto& itr : _interacts)
	{
		if (itr->m_isButton && !itr->m_interacted)
		{
			return false;
		}
	}

	return true;
}

Collider* Level::GetCollider()
{
	return levelCol;
}

Level::Level(sf::String _spritePath)
{
	// Initialising variables and loading sprites, images and textures
	levelBg = rand() % 3;
	levelTemp = levelBg;
	levelIndex = -3;
	levelsCompleted = 0;

	levelCanvasSprite = new sf::Sprite();
	levelCanvasTitle = new sf::Texture();
	levelCanvasTutorial = new sf::Texture();
	levelCanvasTexture1 = new sf::Texture();
	levelCanvasTexture2 = new sf::Texture();
	levelCanvasTexture3 = new sf::Texture();
	levelCanvasTextureDeath = new sf::Texture();

	if (!levelCanvasTitle->loadFromFile("levels/level_main.png"))
	{
		std::cout << "Error: loading level image";
	}

	levelCanvasSprite->setTexture(*levelCanvasTitle);

	if (!levelCanvasTutorial->loadFromFile("levels/tutorial.png"))
	{
		std::cout << "Error: loading level image";
	}

	if (!levelCanvasTexture1->loadFromFile("levels/level_1.png"))
	{
		std::cout << "Error: Loading level image";
	}

	if (!levelCanvasTexture2->loadFromFile("levels/level_2.png"))
	{
		std::cout << "Error: Loading level image";
	}

	if (!levelCanvasTexture3->loadFromFile("levels/level_3.png"))
	{
		std::cout << "Error: Loading level image";
	}

	if (!levelCanvasTextureDeath->loadFromFile("levels/game_over.png"))
	{
		std::cout << "Error: Loading level image";
	}

	levelCol = new Collider(sf::Vector2f(levelCanvasSprite->getLocalBounds().width, levelCanvasSprite->getLocalBounds().height), true);
}

Level::~Level()
{
	// Deallocating memory
	delete levelCanvasSprite, levelCanvasTitle, levelCanvasTutorial, levelCanvasTexture1, levelCanvasTexture2, levelCanvasTexture3, levelCanvasTextureDeath, levelCol;

	levelCanvasSprite = nullptr;
	levelCanvasTitle = nullptr;
	levelCanvasTutorial = nullptr;
	levelCanvasTexture1 = nullptr;
	levelCanvasTexture2 = nullptr;
	levelCanvasTexture3 = nullptr;
	levelCanvasTextureDeath = nullptr;
	levelCol = nullptr;
}
