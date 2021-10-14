#include <SFML/Graphics.hpp>

#pragma once

class Particle
{
private:
	// Particle shape and speed
	sf::CircleShape* particle;
	sf::Vector2f velocity;

	// Bool for deletion
	bool m_isFinished;

public:

	// Methods
	void Update();

	// Getters
	sf::CircleShape* GetParticle()	{ return particle;		};
	bool GetIsFinished()			{ return m_isFinished;	};
;

	Particle(sf::Color _colour, sf::Vector2f _pos);
	~Particle();
};