#include <SFML/Graphics.hpp>
#include "Box2d.h"
#include "Tag Enum.h"

#pragma once

class Object
{
protected:
	sf::Image* m_image;
	sf::Sprite* m_sprite;
	sf::Texture* m_texture;
	sf::RectangleShape* m_colliderBounds;
	Box2d* box2d;
	Tag tag;
	b2World* world;
	float m_scale;

	sf::Clock m_clock;
	sf::Time m_time;

public:
	Object();
	virtual ~Object();

	sf::Sprite* GetSprite()			{ return m_sprite;			};
	sf::RectangleShape* GetShape()	{ return m_colliderBounds;	};
	Tag GetTag()					{ return tag;				};

	virtual void Update() {};
};