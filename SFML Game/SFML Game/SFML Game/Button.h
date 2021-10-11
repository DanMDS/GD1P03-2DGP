#include <SFML/Graphics.hpp>
#include "Interactable.h"
#include "Player.h"

#pragma once

class Button : public Interactable
{
private:
	// Textures and boolean for pressed and not pressed
	sf::Texture* m_buttonTextureUp;
	sf::Texture* m_buttonTextureDown;

	bool m_isPressed;

public:
	// Methods 
	bool IsPressed();
	void Update();

	sf::Sprite* GetSprite();

	Button(sf::Vector2f _pos);
	~Button();
};