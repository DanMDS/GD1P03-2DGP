#include "Button.h"
#include <iostream>

bool Button::IsPressed()
{
	return m_isPressed;
}

void Button::Update()
{
	if (m_interacted && !m_isPressed)
	{
		std::cout << "button pressed";
		m_intSprite->setTexture(*m_buttonTextureDown);
		m_isPressed = true;
	}
}

sf::Sprite* Button::GetSprite()
{
	return m_intSprite;
}

Button::Button(sf::Vector2f _pos)
{
	m_isPressed = false;
	m_isButton = true;
	m_isDoor = false;

	m_intSprite = new sf::Sprite();
	m_buttonTextureDown = new sf::Texture();
	m_buttonTextureUp = new sf::Texture();

	if (!m_buttonTextureDown->loadFromFile("sprites/button_down.png"))
	{
		std::cout << "Error: loading button down sprite";
	}

	if (!m_buttonTextureUp->loadFromFile("sprites/button_up.png"))
	{
		std::cout << "Error: loading button up sprite";
	}
	m_intSprite->setTexture(*m_buttonTextureUp);

	m_intSprite->setOrigin(sf::Vector2f(m_intSprite->getGlobalBounds().width / 2, m_intSprite->getGlobalBounds().height / 2));

	m_intSprite->setPosition(_pos);

	pos = _pos;
}

Button::~Button()
{
	delete m_buttonTextureUp;
	delete m_buttonTextureDown;

	m_buttonTextureDown = nullptr;
	m_buttonTextureUp= nullptr;
}
