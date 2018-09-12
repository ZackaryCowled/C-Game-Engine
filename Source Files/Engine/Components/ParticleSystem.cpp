//Internal includes
#include "Application.h"

//External includes
#include <GL\glew.h>

//Creates and initializes a ParticleSystem instance (Default constructor)
ParticleSystem::ParticleSystem()
{
	//Initialize particle system
	m_particles = nullptr;
	m_maxParticles = 0;
	m_lastDrawTime = 0.0f;
	m_vao[0] = 0;
	m_vao[1] = 0;
	m_vbo[0] = 0;
	m_vbo[1] = 0;
	SetDiffuseMapTextureSampler("Textures/DefaultParticle.png");
	ParticleSystemManager::RegisterParticleSystem(this);
}

//Releases the particle systems resources
ParticleSystem::~ParticleSystem()
{
	//If the particles are valid
	if (m_particles != nullptr)
	{
		//Delete the particles
		delete[] m_particles;

		//Delete GPU resources
		glDeleteVertexArrays(2, m_vao);
		glDeleteBuffers(2, m_vbo);
		glDeleteTextures(1, &m_diffuseMapTextureSampler);

		//Unregister particle system
		ParticleSystemManager::UnregisterParticleSystem(this);
	}
}

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
void ParticleSystem::Initialize(unsigned int maxParticles, float minLifespan, float maxLifespan, float minVelocity, float maxVelocity, float startSize, float endSize, const vec4& startColor, const vec4 endColor)
{
	//Initialize Particle system
	m_maxParticles = maxParticles;
	m_lifespanMin = minLifespan;
	m_lifespanMax = maxLifespan;
	m_velocityMin = minVelocity;
	m_velocityMax = maxVelocity;
	m_startSize = startSize;
	m_endSize = endSize;
	m_startColor = startColor;
	m_endColor = endColor;
	m_particles = new Particle[maxParticles];
	m_activeBuffer = 0;
	CreateBuffers();
}

//Returns the minimum amount of time a particle in the particle system can live for
const float ParticleSystem::GetMinLife()
{
	//Return the minimum amount of time a particle in the particle system can live for
	return m_lifespanMin;
}

//Returns the maximum amount of time a particle in the particle system can live for
const float ParticleSystem::GetMaxLife()
{
	//Return the maximum amount of time a particle in the particle system can live for
	return m_lifespanMax;
}

//Returns the particle systems particle start size
const float ParticleSystem::GetStartSize()
{
	//Return the particle systems particle start size
	return m_startSize;
}

//Returns the particle systems particle end size
const float ParticleSystem::GetEndSize()
{
	//Return the particle systems particle end size
	return m_endSize;
}

//Returns the particle systems particle start color
const vec4 ParticleSystem::GetStartColor()
{
	//Return the particle systems particle start color
	return m_startColor;
}

//Returns the particle systems particle end color
const vec4 ParticleSystem::GetEndColor()
{
	//Return the particle systems particle end color
	return m_endColor;
}

//Returns the particle systems diffuse map texture sampler
const unsigned int ParticleSystem::GetDiffuseMapTextureSampler()
{
	//Return the particle systems diffuse map texture sampler
	return m_diffuseMapTextureSampler;
}

//Sets the particle systems diffuse map texture sampler to use the specified texture
//textureFilepath - The location, name and file extension of the texture
void ParticleSystem::SetDiffuseMapTextureSampler(const string& textureFilepath)
{
	//Load the specified texture
	m_diffuseMapTextureSampler = TextureManager::LoadTexture(textureFilepath);
}

//Updates the particle system
void ParticleSystem::Update()
{
	//Bind the particle systems active buffer
	glBindVertexArray(m_vao[m_activeBuffer]);

	//Bind the update buffer to the transform feedback buffer
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_vbo[!m_activeBuffer]);

	//Begin transform feedback
	glBeginTransformFeedback(GL_POINTS);

	//Update the particle system
	glDrawArrays(GL_POINTS, 0, m_maxParticles);

	//End transform feedback
	glEndTransformFeedback();

	//Unbind the update buffer from the transform feedback buffer
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

	//Swap the particle systems active buffer
	m_activeBuffer = !m_activeBuffer;
}

//Renders the particle system
void ParticleSystem::Render()
{
	//Bind the particle systems active vertex array object
	glBindVertexArray(m_vao[m_activeBuffer]);

	//Draw the particle systems particles
	glDrawArrays(GL_POINTS, 0, m_maxParticles);

	//Unbind the particle systems inactive vertex array object
	glBindVertexArray(0);
}

//Creates the particle systems buffers
void ParticleSystem::CreateBuffers()
{
	//Create particle system buffers
	glGenVertexArrays(2, m_vao);
	glGenBuffers(2, m_vbo);

	//Setup the first buffer
	glBindVertexArray(m_vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(Particle), m_particles, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 12);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 24);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 28);

	//Setup the second buffer
	glBindVertexArray(m_vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(Particle), NULL, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 12);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 24);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), ((char*)0) + 28);

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}