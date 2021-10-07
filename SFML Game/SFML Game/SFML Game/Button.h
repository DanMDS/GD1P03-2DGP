#include <SFML/Graphics.hpp>
#include "Interactable.h"
#include "Player.h"

#pragma once

class Button : public Interactable
{
private:
	sf::Texture* m_buttonTextureUp;
	sf::Texture* m_buttonTextureDown;

	bool m_isPressed;

public:
	bool IsPressed();
	void Update();

	sf::Sprite* GetSprite();

	Button(sf::Vector2f _pos);
	~Button();
};