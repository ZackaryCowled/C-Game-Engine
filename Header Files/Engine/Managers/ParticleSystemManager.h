//Pragma comments
#pragma once

//External includes
#include <vector>

//Using directives
using std::vector;

//Forward declarations
class ParticleSystem;

//Singleton object used for managing the applications particle system components
class ParticleSystemManager
{
public:
	//Returns the particle system at the specified index in the applications particle system container
	static ParticleSystem* GetParticleSystemAt(const unsigned int index);
	
	//Returns the number of particle systems in the applications particle system container
	static const unsigned int GetParticleSystemCount();
	
	//Registers the specified particle system
	static void RegisterParticleSystem(ParticleSystem* p_particleSystem);
	
	//Unregisters the specified particle system
	static void UnregisterParticleSystem(ParticleSystem* p_particleSystem);

private:
	//Container for storing the applications particle systems
	static vector<ParticleSystem*> m_particleSystemContainer;
};