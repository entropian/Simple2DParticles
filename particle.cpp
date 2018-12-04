#include <cassert>
#include <cmath>
#include "particle.h"

static const float G = 0.6f;
static const float modifier = 0.01;

Particle::Particle():x(0.0f), y(0.0f), vx(0.0f), vy(0.0f){}

Particle::Particle(const float x, const float y, const float vx, const float vy):x(x), y(y), vx(vx), vy(vy)
{   
    assert(x >= 0.0f && x < 1.0f);
    assert(y > 0.0f && y <= 1.0f); // Semantic cooupling with Canvas        
}

void Particle::updatePosition(const float delta_t, const float cog_x, const float cog_y, const float damping)
{
    vx *= 1.0f - ((1.0f - damping) * delta_t);
    vy *= 1.0f - ((1.0f - damping) * delta_t);

    float cog_dist_x = cog_x - x;
    float cog_dist_y = cog_y - y;
    float dist_to_cog_squared = cog_dist_x * cog_dist_x + cog_dist_y * cog_dist_y;
    if(dist_to_cog_squared < 0.001f)
    {
        dist_to_cog_squared = 0.001f;
    }
    dist_to_cog = sqrtf(dist_to_cog_squared);
    // f = G*m1*m2 / r*r
    // Assume m1 == m2 == 1?
    float f = G / dist_to_cog_squared;
    float f_dir_x = cog_dist_x / dist_to_cog;
    float f_dir_y = cog_dist_y / dist_to_cog;
    float f_x = f * f_dir_x * delta_t * modifier;
    float f_y = f * f_dir_y * delta_t * modifier;
    vx += f_x; // Iffy notation
    vy += f_y;

    x += vx * delta_t;
    y += vy * delta_t;
    if(x >= 1.0f)
    {
        x -= x - 1.0f + 0.0001f;
        vx = -vx;
    }
    if(x < 0.0f)
    {
        x = -x;
        vx = -vx;
    }
    if(y > 1.0f)
    {
        y -= y - 1.0f;
        vy = -vy;
    }
    if(y <= 0.0f)
    {
        y = -y + 0.0001f;
        vy = -vy;
    }
}

void Particle::setX(const float x)
{
    this->x = x;
}

float Particle::getX() const
{
    return x;
}

void Particle::setY(const float y)
{
    this->y = y;
}

float Particle::getY() const
{
    return y;
}

void Particle::setVx(const float vx)
{
    this->vx = vx;
}

float Particle::getVx() const
{
    return vx;
}

void Particle::setVy(const float vy)
{
    this->vy = vy;
}

float Particle::getVy() const
{
    return vy;
}

float Particle::getDistToCOG() const
{
    return dist_to_cog;
}

void Particle::setDistToCOG(const float d)
{
	dist_to_cog = d;
}