#include <SFML/Graphics.hpp>

#pragma once

class Particle
{
private:
	// Particle shape and speed
	sf::CircleShape* particle;
	sf::Vector2f velocity;

public:
	// Bool for deletion
	bool m_isFinished;

	// Methods
	sf::CircleShape* GetParticle();

	void Update();

	Particle(sf::Color _colour, sf::Vector2f _pos);
	~Particle();
};