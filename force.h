#pragma once
#include "particle.h"


class ForceEmitter
{
public:
	virtual void apply(Particle& p, const float delta_t) = NULL;
	virtual void update(const float delta_t) = NULL;
};

class Gravity : ForceEmitter
{
public:
	Gravity(const float damping,
		const float orbit_center_x = 0.5f, const float orbit_center_y = 0.5f,
		const float orbit_radius = 0.05f);
	void apply(Particle& p, const float delta_t);
	void update(const float delta_t);
	float getX() const;
	void setX(const float x);
	float getY() const;
	void setY(const float y);
private:
	float x, y;		// Center of gravity
	float orbit_center_x, orbit_center_y;
	float orbit_radius;
	float time;
	float damping;
};