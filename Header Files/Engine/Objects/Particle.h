//Pragma comments
#pragma once

//External includes
#include <glm\glm.hpp>

//Using directives
using namespace glm;

//Structure that represents a particle
struct Particle
{
	//Creates and initializes a particle instance
	Particle();

	//The particles local position
	vec3 position;

	//The particles velocity
	vec3 velocity;

	//The amount of time the particle has lived for
	float lifetime;

	//The maximum amount of time the particle can live for
	float lifespan;
};