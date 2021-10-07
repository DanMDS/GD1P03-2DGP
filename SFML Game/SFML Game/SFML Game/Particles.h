#include <SFML/Graphics.hpp>

#pragma once

class Particle
{
private:
	sf::CircleShape* particle;
	sf::Vector2f velocity;

public:
	bool m_isFinished;

	sf::CircleShape* GetParticle();

	void Update();

	Particle(sf::Color _colour, sf::Vector2f _pos);
	~Particle();
};