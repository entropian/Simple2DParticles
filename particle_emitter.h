#pragma once
#include "particle.h"
#include <vector>

class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(const float x, const float y, const float p_per_sec);
	void emit(std::vector<Particle>& output, const float delta_t);
private:
	float x, y;
	float p_per_sec;
};