#include "particle_emitter.h"
ParticleEmitter::ParticleEmitter():x(0.15f), y(0.15f), p_per_sec(1000.0f) {}
ParticleEmitter::ParticleEmitter(const float x, const float y, const float p_per_sec)
	:x(x), y(y), p_per_sec(p_per_sec) {}


void ParticleEmitter::emit(std::vector<Particle>& output, const float delta_t)
{
	float ratio = delta_t * p_per_sec;
	int output_size = int(delta_t * p_per_sec);
	if (output_size == 0)
	{
		float r = float(rand()) / float(RAND_MAX);
		if (r < ratio)
			output_size = 1;
	}
	output.resize(output_size);
	for(auto &p : output)
	{
		float a = (float(rand()) / float(RAND_MAX) * 2.0f - 1.0f) * 0.05f;
		float b = (float(rand()) / float(RAND_MAX) * 2.0f - 1.0f) * 0.05f;
		p = Particle(x, y, a, b);
	}
}