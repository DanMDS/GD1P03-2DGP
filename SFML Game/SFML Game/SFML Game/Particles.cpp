#include "Particles.h"

sf::CircleShape* Particle::GetParticle()
{
	return particle;
}

void Particle::Update()
{
	// Updating particle positin and is finished boolean
	particle->setRadius(particle->getRadius() - 0.2);
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
	velocity = sf::Vector2f(rand() % 11 - 5, rand() % 11 - 5);
}

Particle::~Particle()
{
	// Deallocating memory
	delete particle;
	particle = nullptr;
}
