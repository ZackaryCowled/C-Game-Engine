//Internal includes
#include "ParticleSystemManager.h"
#include "Application.h"

//Initializes the particle system managers particle system container
vector<ParticleSystem*> InitializeParticleSystemContainer()
{
	//Return an empty particle system container
	return vector<ParticleSystem*>();
}

//Initialize static particle system manager attributes
vector<ParticleSystem*> ParticleSystemManager::m_particleSystemContainer(InitializeParticleSystemContainer());

//Returns the particle system at the specified index in the applications particle system container
ParticleSystem* ParticleSystemManager::GetParticleSystemAt(const unsigned int index)
{
	//Return the particle system at the specified index in the applications particle system container
	return m_particleSystemContainer[index];
}

//Returns the number of particle systems in the applications particle system container
const unsigned int ParticleSystemManager::GetParticleSystemCount()
{
	//Return the number of particle systems in the applications particle system container
	return (unsigned int)m_particleSystemContainer.size();
}

//Registers the specified particle system
void ParticleSystemManager::RegisterParticleSystem(ParticleSystem* p_particleSystem)
{
	//Register the specified particle system
	m_particleSystemContainer.push_back(p_particleSystem);
}

//Unregisters the specified particle system
void ParticleSystemManager::UnregisterParticleSystem(ParticleSystem* p_particleSystem)
{
	//For each particle system in the applications particle system container
	for (unsigned int particleSystemIndex = 0; particleSystemIndex < m_particleSystemContainer.size(); particleSystemIndex++)
	{
		//If the particle system is the specified particle system
		if (m_particleSystemContainer[particleSystemIndex] == p_particleSystem)
		{
			//Erase the particle system from the applications particle system container
			m_particleSystemContainer.erase(m_particleSystemContainer.begin() + particleSystemIndex);

			//Return from the function
			return;
		}
	}
}