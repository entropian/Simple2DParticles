#pragma once
#include "particle.h"


class Gravity
{
public:
	Gravity(const float damping,
		const float orbit_center_x = 0.5f, const float orbit_center_y = 0.5f,
		const float orbit_radius = 0.05f);
	
	void update(const float delta_t);

	float getX() const;
	void setX(const float x);

	float getY() const;
	void setY(const float y);

	float getDamping()const;
	void setDamping(const float damping);

	// Apply force on particle p over delta_t
	__forceinline void apply(Particle& p, const float delta_t)
	{
		static const float G = 0.6f;
		static const float modifier = 0.01f;
		float px = p.getX();
		float py = p.getY();
		float vx = p.getVx();
		float vy = p.getVy();
		const float dampened = 1.0f - ((1.0f - damping) * delta_t);
		vx *= 1.0f - ((1.0f - damping) * delta_t);
		vy *= 1.0f - ((1.0f - damping) * delta_t);

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
		vx += f_x;
		vy += f_y;

		px += vx * delta_t;
		py += vy * delta_t;
		if (px >= 1.0f)
		{
			px -= px - 1.0f + 0.0001f;
			vx = -vx;
		}
		if (px < 0.0f)
		{
			px = -px;
			vx = -vx;
		}
		if (py > 1.0f)
		{
			py -= py - 1.0f;
			vy = -vy;
		}
		if (py <= 0.0f)
		{
			py = -py + 0.0001f;
			vy = -vy;
		}
		p.setX(px);
		p.setY(py);
		p.setVx(vx);
		p.setVy(vy);
	}
private:
	float x, y;		// Center of gravity
	float orbit_center_x, orbit_center_y;
	float orbit_radius;
	float time;
	float damping;
};