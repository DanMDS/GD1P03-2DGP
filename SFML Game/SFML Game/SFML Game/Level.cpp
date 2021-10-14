#include <iostream>
#include <string>
#include "Level.h"

/*
	Function: ChangeLevel()
	Returns: void
	Parametres: Player* _player, std::vector<Enemy*> _enemies, int _index
	Summary: Changes to a specific level depending on index. Index values are as follows:
		   -4: random level, random between 3 level sprites
		   -3: title screen, title sprite
		   -2: tutorial, tutorial sprite
		   -1: death screen, death sprite
		0 - 9: specific level, random between 3 level sprites
*/
void Level::ChangeLevel(Player* _player, std::vector<Enemy*> _enemies, int _index)
{
	// Randomizing level or setting to a specific one depending on _index, setting texture accordingly
	if (_index == -4)
	{
		m_levelTemp = m_levelIndex;
		while (m_levelIndex == m_levelTemp)
		{
			m_levelIndex = rand() % 10;
		}

		m_levelTemp = m_levelBg;
		while (m_levelBg == m_levelTemp || m_levelBg < 0)
		{
			m_levelBg = rand() % 3;
		}
	}
	else
	{
		m_levelIndex = _index;
		switch (m_levelIndex)
		{
		case -3:
			m_levelBg = -3;

			break;
		case -2:
			m_levelBg = -2;
			break;

		case -1:
			m_levelBg = -1;

			break;
		}
	}

	switch (m_levelBg)
	{
	case -3:
		m_levelCanvasSprite->setTexture(*m_levelCanvasTitle);
		break;
	case -2:
		m_levelCanvasSprite->setTexture(*m_levelCanvasTutorial);
		break;
	case -1:
		m_levelCanvasSprite->setTexture(*m_levelCanvasTextureDeath);
		break;
	case 0:
		m_levelCanvasSprite->setTexture(*m_levelCanvasTexture1);
		break;
	case 1:
		m_levelCanvasSprite->setTexture(*m_levelCanvasTexture2);
		break;
	case 2:
		m_levelCanvasSprite->setTexture(*m_levelCanvasTexture3);
		break;
	}

	// Moving and scaling obstacles based on level index
	m_levelCol->UpdateColliders(&m_levelIndex);

	// Resetting player position
	_player->SetPlayerPosition(m_playerSpawnPoint);
}

/*
	Function: LevelEndCheck()
	Returns: bool
	Parametres: int _enemiesRemaining, std::vector<Interactable*> _interacts
	Summary: Checks if the level is over depending on the number of enemies and buttons left, returns true
		or false accordingly
*/
bool Level::LevelEndCheck(int _enemiesRemaining, std::vector<Interactable*> _interacts)
{
	// Checking if the level can be ended
	if (_enemiesRemaining != 0)
	{
		return false;
	}

	for (auto& itr : _interacts)
	{
		if (itr->GetIsButton() && !itr->GetInteracted())
		{
			return false;
		}
	}

	return true;
}

Level::Level(sf::String _spritePath)
{
	// Initialising variables and loading sprites, images and textures
	m_levelBg = rand() % 3;
	m_levelTemp = m_levelBg;
	m_levelIndex = -3;
	m_levelsCompleted = 0;

	m_levelCanvasSprite = new sf::Sprite();
	m_levelCanvasTitle = new sf::Texture();
	m_levelCanvasTutorial = new sf::Texture();
	m_levelCanvasTexture1 = new sf::Texture();
	m_levelCanvasTexture2 = new sf::Texture();
	m_levelCanvasTexture3 = new sf::Texture();
	m_levelCanvasTextureDeath = new sf::Texture();

	if (!m_levelCanvasTitle->loadFromFile("levels/level_main.png"))
	{
		std::cout << "Error: loading level image";
	}

	m_levelCanvasSprite->setTexture(*m_levelCanvasTitle);

	if (!m_levelCanvasTutorial->loadFromFile("levels/tutorial.png"))
	{
		std::cout << "Error: loading level image";
	}

	if (!m_levelCanvasTexture1->loadFromFile("levels/level_1.png"))
	{
		std::cout << "Error: Loading level image";
	}

	if (!m_levelCanvasTexture2->loadFromFile("levels/level_2.png"))
	{
		std::cout << "Error: Loading level image";
	}

	if (!m_levelCanvasTexture3->loadFromFile("levels/level_3.png"))
	{
		std::cout << "Error: Loading level image";
	}

	if (!m_levelCanvasTextureDeath->loadFromFile("levels/game_over.png"))
	{
		std::cout << "Error: Loading level image";
	}

	m_levelCol = new Collider(sf::Vector2f(m_levelCanvasSprite->getLocalBounds().width, m_levelCanvasSprite->getLocalBounds().height), true);
}

Level::~Level()
{
	// Deallocating memory
	delete m_levelCanvasSprite, m_levelCanvasTitle, m_levelCanvasTutorial, m_levelCanvasTexture1, m_levelCanvasTexture2, m_levelCanvasTexture3, m_levelCanvasTextureDeath, m_levelCol;

	m_levelCanvasSprite = nullptr;
	m_levelCanvasTitle = nullptr;
	m_levelCanvasTutorial = nullptr;
	m_levelCanvasTexture1 = nullptr;
	m_levelCanvasTexture2 = nullptr;
	m_levelCanvasTexture3 = nullptr;
	m_levelCanvasTextureDeath = nullptr;
	m_levelCol = nullptr;
}
