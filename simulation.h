#pragma once
#include <vector>
#include "particle.h"
#include "force.h"

class Viewport;
class Canvas;

class Simulation
{
public:
    Simulation(const int num_particles, const float brightness_modifier);
    ~Simulation();

	void run(Canvas* canvas, Viewport* viewport);

    void setForceGravity(Gravity& gravity);    
    void setForceWind(Wind& wind);

    void update(const float delta_t);

    void draw(Canvas* canvas);
private:
    std::vector<Particle> particles;

	Gravity gravity;
    ForceEmitter* force;
    float brightness_modifier;
};
