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
	void Update();

	// Getters
	sf::Sprite* GetSprite()		{ return m_intSprite; };
	bool IsPressed()			{ return m_isPressed; };

	// Constructor/destructor
	Button(sf::Vector2f _pos);
	~Button();
};