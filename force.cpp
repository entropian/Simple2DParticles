#include "force.h"
#include <cmath>

Gravity::Gravity():orbit_center_x(0.5f), orbit_center_y(0.5f), orbit_radius(0.05f){}

Gravity::Gravity(const float ox, const float oy, const float radius)
	:orbit_center_x(ox), orbit_center_y(oy), orbit_radius(radius),
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

Wind::Wind():x(0.0f), y(0.0f), magnitude(0.0f), time(0.0f){}

Wind::Wind(const float x, const float y, const float mag):x(x), y(y), magnitude(mag), time(0.0f){}

void Wind::update(const float delta_t)
{
    // TODO: add something
    time += delta_t;
}

float Wind::getX() const
{
    return x;
}

void Wind::setX(const float v)
{
    x = v;
}

float Wind::getY() const
{
    return y;
}

void Wind::setY(const float v)
{
    y = v;
}
