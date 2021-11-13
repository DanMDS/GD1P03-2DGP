#include "Particles.h"
#include "Object.h"
#include "Tag Enum.h"

#pragma once

class ParticleManager : public Object
{
private:
	// Particle object and vector
	Particle* particle;
	std::vector<Particle*> particlesVec;
	std::vector<Particle*>::iterator itParticlesVec;

public:
	// Methods
	bool IsFinished();

	// Getters
	std::vector<Particle*> GetParticles() { return particlesVec; };

	ParticleManager(sf::Color _colour, sf::Vector2f _pos, int _amount);
	~ParticleManager();
};