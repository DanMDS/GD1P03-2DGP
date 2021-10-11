#include "ParticleManager.h"

bool ParticleManager::IsFinished()
{
	// Checking if particles have finished
	if ((*itParticlesVec)->m_isFinished)
	{
		return true;
	}
	return false;
}

std::vector<Particle*> ParticleManager::GetParticles()
{
	return particlesVec;
}

ParticleManager::ParticleManager(sf::Color _colour, sf::Vector2f _pos, int _amount)
{
	// Creating particles at particle manager location
	for (int i = 0; i < _amount; i++)
	{
		particle = new Particle(_colour, _pos);
		particlesVec.push_back(particle);
	}
	itParticlesVec = particlesVec.begin();
}

ParticleManager::~ParticleManager()
{
	// Deallocating memory
	for (auto& itr : particlesVec)
	{
		delete itr;
		itr = nullptr;
	}
	particlesVec.clear();
}
