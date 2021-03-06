#pragma once
#include <vector>
#include "particle.h"
#include "force.h"
#include "particle_emitter.h"
#include <boost/circular_buffer.hpp>
#include "particle_color.h"

class Simulation;

class UserInterface
{
public:	
	UserInterface(Simulation& sim);
	void runInterface();
private:
	bool adding_force;
	ForceType new_force_type;
	Simulation &sim;
};

class Viewport;
class Canvas;

class Simulation
{
	friend class UserInterface;
public:
    Simulation(const int num_particles, const float brightness_modifier);

	void run(Canvas* canvas, Viewport* viewport);

    void addForceGravity(Gravity& gravity);    
    void addForceWind(Wind& wind);
	//void addParticleEmitter(const float x, const float y, const float p_per_sec,
	//	const float vel_modifier);
	void addParticleEmitter(ParticleEmitter*);
private:
	void update(const float delta_t);
	void draw(Canvas* canvas);
    void dampenParticle(Particle& p, const float delta_t);
	void updateForces(const float delta_t);
    void applyForces(Particle& p, const float delta_t);
	void emitParticles(const float delta_t);

	boost::circular_buffer<Particle> particles;
	std::vector<std::unique_ptr<ForceEmitter>> forces;
    float brightness_modifier;
	//std::vector<ParticleEmitter> p_emitters;
	std::vector<std::unique_ptr<ParticleEmitter>> p_emitters;
	std::unique_ptr<ParticleColorCalculator> p_color_calc;
    float damping;
	std::unique_ptr<UserInterface> ui;
};
