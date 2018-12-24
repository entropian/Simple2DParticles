#include <cmath>
#include "particle_color.h"
#include "util.h"

ParticleColorCalculator::ParticleColorCalculator(const float brightness_modifier) :brightness_modifier(brightness_modifier) {}

ForceColor::ForceColor(const float brightness_modifier) : ParticleColorCalculator(brightness_modifier) {}

void ForceColor::calcColor(float &r, float &g, float &b, const Particle &p)
{
	/*std::vector<float> output {clamp(sqrtf(p.getForceMag()) * 40.0f, 0.0f, 1.0f) * brightness_modifier,
	0.5f * brightness_modifier,
	clamp(1.0f - sqrtf(p.getForceMag()) * 40.0f, 0.0f, 0.8f)};
	return output;*/
	r = clamp(sqrtf(p.getForceMag()) * 40.0f, 0.0f, 1.0f) * brightness_modifier;
	g = 0.5f * brightness_modifier;
	b = clamp(1.0f - sqrtf(p.getForceMag()) * 40.0f, 0.0f, 0.8f);
}