#pragma once
#include <cassert>
#include <cmath>

class Particle
{
public:
    Particle();
    Particle(const float x, const float y, const float vx, const float vy);

    void updatePosition(const float delta_t, const float cog_x, const float cog_y, const float damping);

    void setX(const float x);
    float getX() const;

    void setY(const float y);
    float getY() const;

    void setVx(const float vx);
    float getVx() const;

    void setVy(const float vy);
    float getVy() const;

    float getDistToCOG() const;
	void setDistToCOG(const float d);
private:
    float x, y;
    float vx, vy;
    float dist_to_cog;
};

