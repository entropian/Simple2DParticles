#pragma once
#include <cassert>
#include <cmath>

const float G = 0.6f;
const float modifier = 0.01;

class Particle
{
public:
    Particle():x(0.0f), y(0.0f), vx(0.0f), vy(0.0f){}
    Particle(const float x, const float y, const float vx, const float vy):x(x), y(y), vx(vx), vy(vy)
    {   
        assert(x >= 0.0f && x < 1.0f);
        assert(y > 0.0f && y <= 1.0f); // Semantic cooupling with Canvas        
    }

    void updatePosition(const float delta_t, const float cog_x, const float cog_y, const float damping)
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

    void setX(const float x)
    {
        this->x = x;
    }
    
    float getX() const
    {
        return x;
    }

    void setY(const float y)
    {
        this->y = y;
    }

    float getY() const
    {
        return y;
    }

    void setVx(const float vx)
    {
        this->vx = vx;
    }
    
    float getVx() const
    {
        return vx;
    }

    void setVy(const float vy)
    {
        this->vy = vy;
    }

    float getVy() const
    {
        return vy;
    }

    float getDistToCOG() const
    {
        return dist_to_cog;
    }
private:
    float x, y;
    float vx, vy;
    float dist_to_cog;
};

