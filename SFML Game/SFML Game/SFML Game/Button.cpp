#include "Button.h"
#include <iostream>

/*
	Function: Update()
	Returns: void
	Parametres: none
	Description: Updates sprite and m_isPressed boolean when player interacts with it,
		virtual function inherited from interactable
*/
void Button::Update()
{
	// Setting to pressed when pressed
	if (m_interacted && !m_isPressed)
	{
		m_intSprite->setTexture(*m_buttonTextureDown);
		m_isPressed = true;
	}
}

Button::Button(sf::Vector2f _pos)
{
	// Initialising variables
	m_isPressed = false;
	m_isButton = true;
	m_isDoor = false;

	// Loading sprites and textures
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

	// Setting position
	pos = _pos;
}

Button::~Button()
{
	// Deallocating memory
	delete m_buttonTextureUp;
	delete m_buttonTextureDown;

	m_buttonTextureDown = nullptr;
	m_buttonTextureUp= nullptr;
}
