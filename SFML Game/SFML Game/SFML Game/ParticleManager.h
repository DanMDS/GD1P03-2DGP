#include "Particles.h"

#pragma once

class ParticleManager
{
private:
	// Particle object and vector
	Particle* particle;
	std::vector<Particle*> particlesVec;
	std::vector<Particle*>::iterator itParticlesVec;

public:
	// Methods
	bool IsFinished();

	std::vector<Particle*> GetParticles();

	ParticleManager(sf::Color _colour, sf::Vector2f _pos, int _amount);
	~ParticleManager();
};