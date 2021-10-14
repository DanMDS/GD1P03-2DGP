#include "Particles.h"

/*
	Function: Update()
	Returns: void
	Parametres: none
	Summary: Updates size, radius and position based on randomised end point, the sets the is finished
		bool to true
*/
void Particle::Update()
{
	// Updating particle positin and is finished boolean
	particle->setRadius(particle->getRadius() - 0.2f);
	particle->setPosition(sf::Vector2f(particle->getPosition().x + velocity.x, particle->getPosition().y + velocity.y));
	
	if (particle->getRadius() <= 0)
	{
		particle->setFillColor(sf::Color::Transparent);
		m_isFinished = true;
	}
}

Particle::Particle(sf::Color _colour, sf::Vector2f _pos)
{
	// Initalising variables and particle shapes
	m_isFinished = false;
	particle = new sf::CircleShape(5);
	particle->setOrigin(particle->getGlobalBounds().width, particle->getGlobalBounds().height);
	particle->setFillColor(_colour);
	particle->setOutlineThickness(1);
	particle->setOutlineColor(sf::Color::Black);
	particle->setPosition(_pos);
	velocity = sf::Vector2f(float(rand() % 11 - 5), float(rand() % 11 - 5));
}

Particle::~Particle()
{
	// Deallocating memory
	delete particle;
	particle = nullptr;
}
