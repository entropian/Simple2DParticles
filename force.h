#pragma once
#include "particle.h"

class ForceEmitter
{
public:
    virtual void update(const float delta_t) = 0;
    virtual void apply(Particle& p, const float delta_t) = 0;
    virtual void calcForce(float& x, float& y, const Particle& p, const float delta_t) = 0;
};


class Gravity : ForceEmitter
{
public:
    Gravity();
	Gravity(const float orbit_center_x, const float orbit_center_y,
		const float orbit_radius = 0.05f);
	
	void update(const float delta_t);

	float getX() const;
	void setX(const float x);

	float getY() const;
	void setY(const float y);
    
	//float getDamping()const;
	//void setDamping(const float damping);

	// Apply force on particle p over delta_t
	__forceinline void apply(Particle& p, const float delta_t)
	{
		float px = p.getX();
		float py = p.getY();
		float vx = p.getVx();
		float vy = p.getVy();

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
		p.setVx(vx);
		p.setVy(vy);
	}

    void calcForce(float& x, float& y, const Particle& p, const float delta_t)
    {
        
    }
private:
    static constexpr float G = 0.6f;
    static constexpr float modifier = 0.01f;                
	float x, y;		// Center of gravity
	float orbit_center_x, orbit_center_y;
	float orbit_radius;
	float time;
};


class Wind : ForceEmitter
{
public:
    Wind();
    Wind(const float x, const float y, const float mag);
    void update(const float delta_t);

    float getX() const;
    void setX(const float v);

    float getY() const;
    void setY(const float v);

    __forceinline void apply(Particle& p, const float delta_t)
    {
		float vx = p.getVx();
		float vy = p.getVy();
        vx += x * magnitude;
        vy += y * magnitude;
		p.setVx(vx);
		p.setVy(vy);
    }

    void calcForce(float& x, float& y, const Particle& p, const float delta_t)
    {

    }
private:
    float x, y;
    float magnitude;
    float time;
};
