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
    Particle(const float x, const float y, const float vx, const float vy);

	__forceinline void setX(const float x)
	{
		this->x = x;
	}
	__forceinline float getX() const
	{
		return x;
	}

	__forceinline void setY(const float y)
	{
		this->y = y;
	}
	__forceinline float getY() const
	{
		return y;
	}

	__forceinline void setVx(const float vx)
	{
		this->vx = vx;
	}
	__forceinline float getVx() const
	{
		return vx;
	}

	__forceinline void setVy(const float vy)
	{
		this->vy = vy;
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

