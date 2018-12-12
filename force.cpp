#include "force.h"
#include <cmath>

ForceEmitter::ForceEmitter(const ForceType type) :type(type) {}

ForceType ForceEmitter::getType() const
{
	return type;
}

Gravity::Gravity()
	:ForceEmitter(ForceType::GRAVITY), orbit_center_x(0.5f), orbit_center_y(0.5f), 
	orbit_radius(0.05f), time(0.0f), G(0.6f){}

Gravity::Gravity(const float ox, const float oy, const float radius)
	:ForceEmitter(ForceType::GRAVITY), orbit_center_x(ox), orbit_center_y(oy), 
	orbit_radius(radius), time(0.0f), G(0.6f) {}

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

float Gravity::getCenterX() const
{
	return orbit_center_x;
}

void Gravity::setCenterX(const float a)
{
	orbit_center_x = a;
}

float Gravity::getCenterY() const
{
	return orbit_center_y;
}

void Gravity::setCenterY(const float a)
{
	orbit_center_y = a;
}

float Gravity::getRadius() const
{
	return orbit_radius;
}

void Gravity::setRadius(const float a)
{
	orbit_radius = a;
}

float Gravity::getG() const
{
	return G;
}

void Gravity::setG(const float a)
{
	G = a;
}

Wind::Wind()
	:ForceEmitter(ForceType::WIND), x(0.0f), y(0.0f), magnitude(0.0f), time(0.0f){}

Wind::Wind(const float x, const float y, const float mag)
	:ForceEmitter(ForceType::WIND), x(x), y(y), magnitude(mag), time(0.0f){}

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

float Wind::getMagnitude() const
{
	return magnitude;
}

void Wind::setMagnitude(const float a)
{
	magnitude = a;
}
