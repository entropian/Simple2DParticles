#pragma once
#include "particle.h"

enum class ForceType
{
	NONE,
	GRAVITY,
	WIND
};

class ForceEmitter
{
public:
	ForceEmitter(const ForceType type);
    virtual void update(const float delta_t) = 0;
    virtual void calcForce(float& x, float& y, Particle& p, const float delta_t) = 0;
	ForceType getType() const;
private:
	ForceType type;
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

	float getCenterX() const;
	void setCenterX(const float a);

	float getCenterY() const;
	void setCenterY(const float a);

	float getRadius() const;
	void setRadius(const float a);

	float getG() const;
	void setG(const float a);

    __forceinline void calcForce(float& out_x, float& out_y, Particle& p, const float delta_t)
    {
		auto px = p.getX();
		auto py = p.getY();
		auto vx = p.getVx();
		auto vy = p.getVy();

		auto cog_dist_x = x - px;
		auto cog_dist_y = y - py;
		auto dist_to_cog_squared = cog_dist_x * cog_dist_x + cog_dist_y * cog_dist_y;
		if (dist_to_cog_squared < 0.001f)
		{
			dist_to_cog_squared = 0.001f;
		}
		auto dist_to_cog = sqrtf(dist_to_cog_squared);
		// f = G*m1*m2 / r*r
		// Assume m1 == m2 == 1?
		auto f = G / dist_to_cog_squared;
		auto f_dir_x = cog_dist_x / dist_to_cog;
		auto f_dir_y = cog_dist_y / dist_to_cog;
		out_x = f * f_dir_x * delta_t * modifier;
		out_y = f * f_dir_y * delta_t * modifier;        
    }
private:
    float G;
    static constexpr float modifier = 0.01f;                
	float x, y;
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

	float getMagnitude() const;
	void setMagnitude(const float a);

    void calcForce(float& out_x, float& out_y, Particle& p, const float delta_t)
    {
		out_x = x * magnitude;
		out_y = y * magnitude;
		time += delta_t;
    }
private:
    float x, y;
    float magnitude;
    float time;
};
