#pragma once

#include <SFML/Graphics.hpp>

class OptionButton
{
private:
	sf::Texture* m_rectPlus;
	sf::Texture* m_rectMinus;
	sf::Sprite* m_buttonPlus;
	sf::Sprite* m_buttonMinus;

	std::string m_textStr;
	sf::Text* m_text;
	sf::Font m_font;

	int m_value;
	int m_increment;
	int m_max;
	int m_min;

public:
	OptionButton(sf::Vector2f _pos, sf::Font _font, int _value, int _increment, int _min, int _max, std::string _text, int _index);
	~OptionButton();

	int* CheckButton(sf::Vector2f _mousePos);
	int* GetValue() { return &m_value; }

	void Draw(sf::RenderWindow* _window);
};