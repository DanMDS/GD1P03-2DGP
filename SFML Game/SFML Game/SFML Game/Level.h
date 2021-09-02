#include <SFML/Graphics.hpp>

#pragma once

class Level
{
private:
	sf::Texture canvasTexture;
	sf::Image canvasImage;

	sf::Vector2f dimensions;

	Level();
	~Level();
};