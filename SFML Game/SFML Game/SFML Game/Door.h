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

	bool DoorIsOpen();
	
	sf::Sprite* GetSprite();
	sf::Vector2f GetDoorPosition();

	Door(sf::Vector2f _levelDim);
	~Door();
};