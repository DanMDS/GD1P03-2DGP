#include <SFML/Graphics.hpp>
#include "Box2d.h"

#pragma once

class Object
{
protected:
	sf::Image* m_image;
	sf::Sprite* m_sprite;
	sf::Texture* m_texture;
	sf::RectangleShape* m_colliderBounds;
	Box2d* box2d;
	std::string tag;
	b2World* world;
	float m_scale;

public:
	Object();
	~Object();

	sf::Sprite* GetSprite()			{ return m_sprite;			};
	sf::RectangleShape* GetShape()	{ return m_colliderBounds;	};
	std::string GetTag()			{ return tag;				};

	virtual void Update() {};
};