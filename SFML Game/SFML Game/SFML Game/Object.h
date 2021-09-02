#include <SFML/Graphics.hpp>

#pragma once

class Object
{
private:
	int m_ObjHealth = 1;									// If health is negative, invincible;

	sf::Sprite* m_ObjSprite;								// Member sprite
	sf::Texture* m_ObjTexture;								// Member texture

	sf::Vector2f m_ObjPos;									// Member position

public:
	Object(sf::String _spritePath, sf::Vector2f _objPos);	// Constructor
	~Object();												// Destructor

	sf::Sprite* GetSprite();								// Draw methods
	void UpdateObject();
};