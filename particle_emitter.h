#pragma once
#include "particle.h"
#include <vector>

class ParticleEmitter
{
public:
	ParticleEmitter();
	void emit(std::vector<Particle>& output, const float delta_t);
private:
	float x, y;
	float p_per_sec;
};