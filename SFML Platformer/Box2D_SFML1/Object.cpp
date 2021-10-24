#include "Object.h"

Object::Object()
{
	m_scale = 0.0f;

	m_sprite = new sf::Sprite();
	m_texture = new sf::Texture();

	m_image = nullptr;
	m_colliderBounds = nullptr;
	box2d = nullptr;
	world = nullptr;
}

Object::~Object()
{
	delete m_sprite;
	delete m_texture;
	delete m_image;
	delete m_colliderBounds;
	delete box2d;

	m_sprite = nullptr;
	m_texture = nullptr;
	m_image = nullptr;
	m_colliderBounds = nullptr;
	box2d = nullptr;
}