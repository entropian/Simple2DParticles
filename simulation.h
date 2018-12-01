#pragma once
#include <vector>
#include "particle.h"
#include "canvas.h"

class Viewport;

class Simulation
{
public:
    Simulation(const int num_particles, const float orbit_radius, const float damping,
               const float brightness_modifier);

	void run(Canvas& canvas, Viewport* viewport);

    void update(const float delta_t);

    void draw(Canvas& canvas);
private:
    std::vector<Particle> particles;
    float orbit_center;
    float orbit_radius;
    float damping;
    double time;
    float brightness_modifier;
};
