#pragma once
#include "particle.h"
#include <vector>

enum class ParticleEmitterType
{
	NONE,
	STREAM,
	BURST
};

class ParticleEmitter
{
public:
	virtual void emit(std::vector<Particle> &output, const float delta_t) = 0;
	virtual ParticleEmitterType getType() const;
};

class StreamEmitter : public ParticleEmitter
{
public:
	StreamEmitter();
	StreamEmitter(const float x, const float y, const float p_per_sec,
		const float vel_modifier);
	void emit(std::vector<Particle>& output, const float delta_t) override;
	ParticleEmitterType getType() const override;

	float getX() const;
	void setX(const float a);

	float getY() const;
	void setY(const float a);

	float getParticlesPerSec() const;
	void setParticlesPerSec(const float a);

	float getVelocityModifier() const;
	void setVelocityModifier(const float a);
private:
	float x, y;
	float p_per_sec;
	float vel_modifier;
};