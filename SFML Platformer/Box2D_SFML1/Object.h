#include <SFML/Graphics.hpp>
#include "Box2d.h"

#pragma once

class Object
{
protected:
	sf::Sprite* m_sprite;
	sf::Texture* m_texture;
	sf::RectangleShape* m_colliderBounds;
	Box2d* box2d;

public:
	Object();
	~Object();

	sf::Sprite* GetSprite() { return m_sprite; };

	virtual void Update() {};
};