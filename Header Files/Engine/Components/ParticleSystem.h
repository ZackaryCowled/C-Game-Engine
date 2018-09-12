//Pragma comments
#pragma once

//Precompiler definitions
#define MAX_PARTICLES 1000

//Internal includes
#include "Component.h"
#include "Particle.h"

//Component used for emmiting and controlling particles
class ParticleSystem : public Component
{
public:
	//Creates and initializes a ParticleSystem instance (Default constructor)
	ParticleSystem();

	//Releases the particle systems resources
	~ParticleSystem();

	//Initializes the particle system
	//maxParticles - The maximum number of particles that can exist in the particle system at any given time
	//minLifespan - The minimum amonut of time a particle can live for
	//maxLifespan - The maximum amount of time a particle can live for
	//minVelocity - The minimum velocity a particle can have
	//maxVelocity - The maximum velocity a particle can have
	//startSize - The size particles start with
	//endSize - The size particles end with
	//startColor - The color particles start with
	//endColor - The color particles end with
	void Initialize(unsigned int maxParticles, float minLifespan, float maxLifespan, float minVelocity, float maxVelocity, float startSize, float endSize, const vec4& startColor, const vec4 endColor);

	//Returns the minimum amount of time a particle in the particle system can live for
	const float GetMinLife();

	//Returns the maximum amount of time a particle in the particle system can live for
	const float GetMaxLife();

	//Returns the particle systems particle start size
	const float GetStartSize();

	//Returns the particle systems particle end size
	const float GetEndSize();

	//Returns the particle systems particle start color
	const vec4 GetStartColor();

	//Returns the particle systems particle end color
	const vec4 GetEndColor();

	//Returns the particle systems diffuse map texture sampler
	const unsigned int GetDiffuseMapTextureSampler();

	//Sets the particle systems diffuse map texture sampler to use the specified texture
	//textureFilepath - The location, name and file extension of the texture
	void SetDiffuseMapTextureSampler(const string& textureFilepath);

	//Updates the particle system
	void Update();

	//Renders the particle system
	void Render();

protected:
	//Creates the particle systems buffers
	void CreateBuffers();

private:
	//Array of particles
	Particle* m_particles;

	//The max amount of particle that can exist at any given point in the particle system
	unsigned int m_maxParticles;

	//The minimum amount of time particles can live for
	float m_lifespanMin;

	//The maximum amount of time particles can live for
	float m_lifespanMax;

	//The minimum velocity particles can have
	float m_velocityMin;

	//The maximum velocity particles can have
	float m_velocityMax;

	//The size particles start with
	float m_startSize;

	//The size particles end with
	float m_endSize;

	//The color particles start with
	vec4 m_startColor;

	//The color particles end with
	vec4 m_endColor;

	//Diffuse map texture sampler
	unsigned int m_diffuseMapTextureSampler;

	//The active buffer
	unsigned int m_activeBuffer;

	//The particle systems vertex array objects
	unsigned int m_vao[2];

	//The particle systems vertex buffer objects
	unsigned int m_vbo[2];

	//The time the particle system was last rendered
	float m_lastDrawTime;
};