#include "ParticleManager.h"

bool ParticleManager::IsFinished()
{
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

ParticleManager::ParticleManager(sf::Color _colour, sf::Vector2f _pos)
{
	for (int i = 0; i < 10; i++)
	{
		particle = new Particle(_colour, _pos);
		particlesVec.push_back(particle);
	}
	itParticlesVec = particlesVec.begin();
}

ParticleManager::~ParticleManager()
{
	for (auto& itr : particlesVec)
	{
		delete itr;
		itr = nullptr;
	}
	particlesVec.clear();
}
