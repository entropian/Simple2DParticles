#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "simulation.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "gl/glcode.h"
#include "canvas.h"
#include "util.h"


Simulation::Simulation(const int num_particles, const float brightness_modifier)
    :brightness_modifier(brightness_modifier), p_emitter(), damping(0.8f)
{
    particles.resize(num_particles);
    srand(0);
    std::vector<Particle>::iterator itr;
	for(auto& p : particles)
    {
		float x = float(rand()) / float(RAND_MAX);
		float y = float(rand()) / float(RAND_MAX);
		p = Particle(x, y);
        //itr->setVx(((float(rand()) / float(RAND_MAX)) - 0.5f) * 0.2f);
        //itr->setVy(((float(rand()) / float(RAND_MAX)) - 0.5f) * 0.2f); 
    }
}

Simulation::~Simulation()
{

}

void Simulation::addForceGravity(Gravity& g)
{
    Gravity* gravity = new Gravity();
    *gravity = g;
    forces.push_back(reinterpret_cast<ForceEmitter*>(gravity));
}

void Simulation::addForceWind(Wind& w)
{
    Wind* wind = new Wind();
    *wind = w;
    forces.push_back(reinterpret_cast<ForceEmitter*>(wind));
}

static const double display_time_interval = 1.0;

void Simulation::run(Canvas* canvas, Viewport* viewport)

{
	const double display_time_interval = 1.0;
	double prev_time = glfwGetTime();
	double last_display_time = prev_time;
	bool running = true;
	while (running)
	{
		double current_time = glfwGetTime();
		float delta_t = float(current_time - prev_time);
		update(delta_t);
		canvas->prepDrawing(delta_t);
		draw(canvas);
		viewport->displayImage(canvas->getCanvasData(), canvas->getWidth(), canvas->getHeight());
		if (current_time - last_display_time >= display_time_interval)
		{
			std::cout << 1.0f / delta_t << " FPS\n";
			last_display_time = current_time;
		}
		glfwPollEvents();
		prev_time = current_time;
	}
}

void Simulation::dampenParticle(Particle& p, const float delta_t)
{
    float px = p.getX();
    float py = p.getY();
    float vx = p.getVx();
    float vy = p.getVy();
    const float dampened = 1.0f - ((1.0f - damping) * delta_t);
    vx *= 1.0f - ((1.0f - damping) * delta_t);
    vy *= 1.0f - ((1.0f - damping) * delta_t);
    p.setVx(vx);
    p.setVy(vy);    
}

void Simulation::applyForces(Particle& p, const float delta_t)
{
    float force_x = 0.0f, force_y = 0.0f;
	for(auto& f : forces)
	{
		float fx, fy;
		f->calcForce(fx, fy, p, delta_t);
		force_x += fx;
		force_y += fy;
	}
    p.setVx(p.getVx() + force_x);
    p.setVy(p.getVy() + force_y);
	auto force_mag = sqrtf(force_x * force_x + force_y * force_y);
	p.setForceMag(force_mag);
}

void Simulation::updateForces(const float delta_t)
{
	for (auto& f : forces)
	{
		f->update(delta_t);
	}
}

void Simulation::update(const float delta_t)
{    
	updateForces(delta_t);
    std::vector<Particle>::iterator itr;
	for(auto& p : particles)
    {
        dampenParticle(p, delta_t); // NOTE: moving this out of Gravity noticeably lowered FPS
                                       // inline?
        applyForces(p, delta_t);
		p.updatePosition(delta_t);
    }
	std::vector<Particle> new_particles;
	p_emitter.emit(new_particles, delta_t);
	particles.insert(particles.end(), new_particles.begin(), new_particles.end());
}

void Simulation::draw(Canvas* canvas)
{
    std::vector<Particle>::iterator itr;
	for(auto& p : particles)
    {
            
		/*
        canvas->drawParticle(p.getX(), p.getY(),
                         clamp(0.1 / p.getDistToCOG(), 0.0f, 0.8f) * brightness_modifier,
                         0.5f * brightness_modifier,
                         clamp((1.0 - 0.1 / p.getDistToCOG()), 0.0f, 1.0f) * brightness_modifier);
						 */
		canvas->drawParticle(p.getX(), p.getY(),
			clamp(sqrtf(p.getForceMag()) * 40.0f, 0.0f, 1.0f) * brightness_modifier,
			0.5f * brightness_modifier,
			clamp(1.0f - sqrtf(p.getForceMag()) * 40.0f, 0.0f, 0.8f) * brightness_modifier);
    }
	canvas->calcImage();
}
