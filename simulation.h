#pragma once
#include <vector>
#include "particle.h"
#include "force.h"

class Viewport;
class Canvas;

class Simulation
{
public:
    Simulation(const int num_particles, const float orbit_radius, const float damping,
               const float brightness_modifier);

	void run(Canvas* canvas, Viewport* viewport);

    void update(const float delta_t);

    void draw(Canvas* canvas);
private:
    std::vector<Particle> particles;

	Gravity gravity;
    float brightness_modifier;
};
