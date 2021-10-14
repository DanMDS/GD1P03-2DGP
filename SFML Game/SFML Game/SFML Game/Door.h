#include <SFML/Graphics.hpp>
#include "Interactable.h"
#include "Enemy.h"
#include "Player.h"

#pragma once

class Door : public Interactable
{
private:
	// Bool for texture changing
	bool m_locked;

	// Open and closed textures
	sf::Texture* m_doorClosedTexture;
	sf::Texture* m_doorOpenTexture;

public:
	// Methods
	void Update(bool _levelEnd, sf::Vector2f _playerPos, Player* _player, std::vector<Enemy*> _enemies);
	void DoorLock();

	// Getters
	bool DoorIsOpen()				{ return !m_locked;						};
	sf::Sprite* GetSprite()			{ return m_intSprite;					};
	sf::Vector2f GetDoorPosition()	{ return m_intSprite->getPosition();	};

	// Constructor/destructor
	Door(sf::Vector2i _levelDim);
	~Door();
};