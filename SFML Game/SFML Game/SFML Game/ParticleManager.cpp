#include "ParticleManager.h"

/*
	Function: IsFinished()
	Returns: bool
	Parametres: none
	Summary: Checks if the particles are finished player, returns true or false accordingly
*/
bool ParticleManager::IsFinished()
{
	// Checking if particles have finished
	if ((*itParticlesVec)->GetIsFinished())
	{
		return true;
	}
	return false;
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
