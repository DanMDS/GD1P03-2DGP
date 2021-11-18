#include "OptionButton.h"
#include <iostream>

OptionButton::OptionButton(sf::Vector2f _pos, sf::Font _font, int _value, int _increment, int _min, int _max, std::string _text, int _index)
{
	m_rectMinus = new sf::Texture();
	m_rectPlus = new sf::Texture();
	m_buttonPlus = new sf::Sprite();
	m_buttonMinus = new sf::Sprite();

	if (!m_rectPlus->loadFromFile("sprites/plus.png"))
	{
		std::cout << "Error loading plus button image\n";
	}
	m_buttonPlus->setTexture(*m_rectPlus);

	if (!m_rectMinus->loadFromFile("sprites/minus.png"))
	{
		std::cout << "Error loading minus button image\n";
	}
	m_buttonMinus->setTexture(*m_rectMinus);

	m_textStr = _text;
	m_value = _value;
	m_increment = _increment;
	m_min = _min;
	m_max = _max;

	m_font.loadFromFile("ARIAL.ttf");

	m_text = new sf::Text();

	m_text->setString(m_textStr + std::to_string(m_value));
	m_text->setFont(m_font);
	m_text->setFillColor(sf::Color::Black);
	m_text->setCharacterSize(25);
	m_text->setPosition(sf::Vector2f(50, 50 * _index));

	m_buttonPlus->setPosition(sf::Vector2f(0, 50 * _index));
	m_buttonMinus->setPosition(sf::Vector2f(25, 50 * _index));
}

OptionButton::~OptionButton()
{
	delete m_rectPlus;
	delete m_rectMinus;
	delete m_buttonPlus;
	delete m_buttonMinus;
	delete m_text;

	m_rectPlus = nullptr;
	m_rectMinus = nullptr;
	m_buttonPlus = nullptr;
	m_buttonMinus = nullptr;
	m_text = nullptr;
}

int* OptionButton::CheckButton(sf::Vector2f _mousePos)
{
	if (m_buttonMinus->getGlobalBounds().contains(_mousePos) && m_value > m_min)
	{
		m_value -= m_increment;
	}
	if (m_buttonPlus->getGlobalBounds().contains(_mousePos) && m_value < m_max)
	{
		m_value += m_increment;
	}
	m_text->setString(m_textStr + std::to_string(m_value));
	return &m_value;
}

void OptionButton::Draw(sf::RenderWindow* _window)
{
	_window->draw(*m_buttonPlus);
	_window->draw(*m_buttonMinus);
	_window->draw(*m_text);
}
