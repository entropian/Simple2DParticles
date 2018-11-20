#pragma once
#include <cassert>

class Particle
{
public:
    Particle():x(0.0f), y(0.0f), vx(0.0f), vy(0.0f){}
    Particle(const float x, const float y, const float vx, const float vy):x(x), y(y), vx(vx), vy(vy)
    {   
        assert(x >= 0.0f && x < 1.0f);
        assert(y > 0.0f && y <= 1.0f); // Semantic cooupling with Canvas        
    }

    void updatePosition(const float delta_t)
    {
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
private:
    float x, y;
    float vx, vy;
};

