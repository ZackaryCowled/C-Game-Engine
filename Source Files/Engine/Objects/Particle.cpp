//Internal includes
#include "Particle.h"

//Creates and initializes a particle instance (Default constructor)
Particle::Particle()
{
	//Initialize particle
	position = vec3(0.0f, 0.0f, 0.0f);
	velocity = vec3(0.0f, 0.0f, 0.0f);
	lifetime = 1.0f;
	lifespan = 0.0f;
}