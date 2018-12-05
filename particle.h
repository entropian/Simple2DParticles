#pragma once
#include <cassert>
#include <cmath>

#ifdef __GNUC__
#define __forceinline 
#endif

class Particle
{
public:
    Particle();
	Particle(const float x, const float y, const float vx = 0.0f, const float vy = 0.0f);
		
	__forceinline void updatePosition(const float delta_t)
	{
		x += vx * delta_t;
		y += vy * delta_t;
		if (x >= 1.0f)
		{
			x -= x - 1.0f + 0.0001f;
			vx = -vx;
		}
		if (x < 0.0f)
		{
			x = -x;
			vx = -vx;
		}
		if (y > 1.0f)
		{
			y -= y - 1.0f;
			vy = -vy;
		}
		if (y <= 0.0f)
		{
			y = -y + 0.0001f;
			vy = -vy;
		}
	}

	__forceinline float getX() const
	{
		return x;
	}

	__forceinline float getY() const
	{
		return y;
	}

	__forceinline void setVx(const float a)
	{
		vx = a;
	}
	__forceinline float getVx() const
	{
		return vx;
	}

	__forceinline void setVy(const float a)
	{
		vy = a;
	}
	__forceinline float getVy() const
	{
		return vy;
	}

	__forceinline float getDistToCOG() const
	{
		return dist_to_cog;
	}
	__forceinline void setDistToCOG(const float d)
	{
		dist_to_cog = d;
	}
private:
    float x, y;
    float vx, vy;
    float dist_to_cog;
};

