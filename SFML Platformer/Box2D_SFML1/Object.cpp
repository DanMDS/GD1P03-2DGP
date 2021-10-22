#include "Object.h"

Object::Object()
{
	m_sprite = new sf::Sprite();
	m_texture = new sf::Texture();

	m_colliderBounds = nullptr;
	box2d = nullptr;
}

Object::~Object()
{
	delete m_sprite;
	delete m_texture;
	delete m_colliderBounds;
	delete box2d;

	m_sprite = nullptr;
	m_texture = nullptr;
	m_colliderBounds = nullptr;
	box2d = nullptr;
}