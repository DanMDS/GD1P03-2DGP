#include "Particles.h"

#pragma once

class ParticleManager
{
private:
	Particle* particle;
	std::vector<Particle*> particlesVec;
	std::vector<Particle*>::iterator itParticlesVec;

public:
	bool IsFinished();

	std::vector<Particle*> GetParticles();

	ParticleManager(sf::Color _colour, sf::Vector2f _pos);
	~ParticleManager();
};