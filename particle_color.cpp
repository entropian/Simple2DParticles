#include <cmath>
#include "particle_color.h"
#include "util.h"

ParticleColorCalculator::ParticleColorCalculator(const float brightness_modifier) :brightness_modifier(brightness_modifier) {}

ForceColor::ForceColor(const float brightness_modifier) : ParticleColorCalculator(brightness_modifier) {}

void ForceColor::calcColor(float &r, float &g, float &b, const Particle &p)
{
	r = clamp(sqrtf(p.getForceMag()) * 40.0f, 0.0f, 1.0f) * brightness_modifier;
	g = 0.5f * brightness_modifier;
	b = clamp(1.0f - sqrtf(p.getForceMag()) * 40.0f, 0.0f, 0.8f);
}

VelocityColor::VelocityColor(const float brigntness_modifier) : ParticleColorCalculator(brightness_modifier) {}

void VelocityColor::calcColor(float &r, float &g, float &b, const Particle &p)
{
	r = clamp(p.getVelMag() * 3.0f, 0.0f, 1.0f);
	g = 0.5f;
	b = clamp(1.0f - p.getVelMag() * 3.0f, 0.0f, 0.8f);
}