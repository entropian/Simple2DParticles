#include "force.h"
#include <cmath>

Gravity::Gravity(const float damping,
	const float ox, const float oy, const float or)
	:damping(damping), orbit_center_x(ox), orbit_center_y(oy), orbit_radius(or),
	time(0.0f) {}

void Gravity::update(const float delta_t)
{
	x = cosf(time) * orbit_radius + orbit_center_x;
	y = sinf(time) * orbit_radius + orbit_center_y;
	time += delta_t;
}

static const float G = 0.6f;
static const float modifier = 0.01;
void Gravity::apply(Particle& p, const float delta_t)
{
	float px = p.getX();
	float py = p.getY();
	float vx = p.getVx();
	float vy = p.getVy();
	const float dampened = 1.0f - ((1.0f - damping) * delta_t);
	vx *= 1.0f - ((1.0f - damping) * delta_t);
	vy *= 1.0f - ((1.0f - damping) * delta_t);
	//p.setVx(p.getVx() * dampened);
	//p.setVy(p.getVy() * dampened);

	//float cog_dist_x = x - p.getX();
	//float cog_dist_y = y - p.getY();
	float cog_dist_x = x - px;
	float cog_dist_y = y - py;
	float dist_to_cog_squared = cog_dist_x * cog_dist_x + cog_dist_y * cog_dist_y;
	if (dist_to_cog_squared < 0.001f)
	{
		dist_to_cog_squared = 0.001f;
	}
	p.setDistToCOG(sqrtf(dist_to_cog_squared));
	// f = G*m1*m2 / r*r
	// Assume m1 == m2 == 1?
	float f = G / dist_to_cog_squared;
	float f_dir_x = cog_dist_x / p.getDistToCOG();
	float f_dir_y = cog_dist_y / p.getDistToCOG();
	float f_x = f * f_dir_x * delta_t * modifier;
	float f_y = f * f_dir_y * delta_t * modifier;
	//p.setVx(p.getVx() + f_x); // Iffy notation
	//p.setVy(p.getVy() + f_y);
	vx += f_x; 
	vy += f_y;

	//p.setX(p.getX() + (p.getVx() * delta_t));
	//p.setY(p.getY() + (p.getVy() * delta_t));
	px += vx * delta_t;
	py += vy * delta_t;
	if (px >= 1.0f)
	{
		px -= px - 1.0f + 0.0001f;
		//p.setVx(-p.getVx());
		vx = -vx;
	}
	if (px < 0.0f)
	{
		px = -px;
		//p.setVx(-p.getVx());
		vx = -vx;
	}
	if (py > 1.0f)
	{
		py -= py - 1.0f;
		//p.setVy(-p.getVy());
		vy = -vy;
	}
	if (py <= 0.0f)
	{
		py = -py + 0.0001f;
		//p.setVy(-p.getVy());
		vy = -vy;
	}
	p.setX(px);
	p.setY(py);
	p.setVx(vx);
	p.setVy(vy);
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