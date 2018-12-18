#include "particle_emitter.h"
ParticleEmitter::ParticleEmitter()
	:x(0.00001f), y(0.00001f), p_per_sec(0.0f), vel_modifier(0.0f) {}
ParticleEmitter::ParticleEmitter(const float x, const float y, const float p_per_sec,
	const float vel_modifier)
	:x(x), y(y), p_per_sec(p_per_sec), vel_modifier(vel_modifier) {}


void ParticleEmitter::emit(std::vector<Particle>& output, const float delta_t)
{
	auto ratio = delta_t * p_per_sec;
	auto output_size = int(delta_t * p_per_sec);
	if (output_size == 0)
	{
		auto r = float(rand()) / float(RAND_MAX);
		if (r < ratio)
			output_size = 1;
	}
	output.resize(output_size);
	for(auto &p : output)
	{
		auto a = (float(rand()) / float(RAND_MAX) * 2.0f - 1.0f) * vel_modifier;
		auto b = (float(rand()) / float(RAND_MAX) * 2.0f - 1.0f) * vel_modifier;
		p = Particle(x, y, a, b);
	}
}

float ParticleEmitter::getX() const
{
	return x;
}

void ParticleEmitter::setX(const float a)
{
	x = a;
}

float ParticleEmitter::getY() const
{
	return y;
}

void ParticleEmitter::setY(const float a)
{
	y = a;
}

float ParticleEmitter::getParticlesPerSec() const
{
	return p_per_sec;
}

void ParticleEmitter::setParticlesPerSec(const float a)
{
	p_per_sec = a;
}

float ParticleEmitter::getVelocityModifier() const
{
	return vel_modifier;
}

void ParticleEmitter::setVelocityModifier(const float a)
{
	vel_modifier = a;
}