#pragma once
#include <vector>
#include "particle.h"
#include "force.h"
#include "particle_emitter.h"

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
private:
	void update(const float delta_t);
	void draw(Canvas* canvas);
    void dampenParticle(Particle& p, const float delta_t);

    std::vector<Particle> particles;
    ForceEmitter* force;
    float brightness_modifier;
	ParticleEmitter p_emitter;
    float damping;
};
