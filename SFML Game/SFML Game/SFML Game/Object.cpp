#include <iostream>
#include "Object.h"

Object::Object(sf::String _spritePath, sf::Vector2f _objPos)
{
	m_ObjTexture = new sf::Texture();
	if (!m_ObjTexture->loadFromFile(_spritePath))
	{
		std::cout << "Error: " << std::string(_spritePath) << " failed to load";
	}

	m_ObjSprite = new sf::Sprite();
	m_ObjSprite->setTexture(*m_ObjTexture);

	m_ObjPos = _objPos;

	UpdateObject();
}

Object::~Object()
{
	delete m_ObjTexture;
	delete m_ObjSprite;
}

sf::Sprite* Object::GetSprite()
{
	return m_ObjSprite;
}

void Object::UpdateObject()
{
	m_ObjSprite->setPosition(m_ObjPos);
}
