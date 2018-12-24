#include "particle.h"

Particle::Particle():x(0.0f), y(0.0f), vx(0.0f), vy(0.0f){}

Particle::Particle(const float x, const float y, const float vx, const float vy)
	: x(x), y(y), vx(vx), vy(vy), force_magnitude(0.0f) {}
