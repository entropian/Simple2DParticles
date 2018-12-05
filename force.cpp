#include "force.h"
#include <cmath>

Gravity::Gravity():damping(0.8f), orbit_center_x(0.5f), orbit_center_y(0.5f), orbit_radius(0.05f){}

Gravity::Gravity(const float damping,
	const float ox, const float oy, const float radius)
	:damping(damping), orbit_center_x(ox), orbit_center_y(oy), orbit_radius(radius),
	time(0.0f) {}

void Gravity::update(const float delta_t)
{
	x = cosf(time) * orbit_radius + orbit_center_x;
	y = sinf(time) * orbit_radius + orbit_center_y;
	time += delta_t;
}

float Gravity::getX() const
{
	return x;
}
void Gravity::setX(const float x)
{
	this->x = x;
}
float Gravity::getY() const
{
	return y;
}
void Gravity::setY(const float y)
{
	this->y = y;
}

float Gravity::getDamping() const
{
	return damping;
}

void Gravity::setDamping(const float d)
{
	damping = d;
}
