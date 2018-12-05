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
    :brightness_modifier(brightness_modifier), force(nullptr)
{
    particles.resize(num_particles);
    srand(0);
    std::vector<Particle>::iterator itr;
    for(itr = particles.begin(); itr < particles.end(); itr++)
    {
		float x = float(rand()) / float(RAND_MAX);
		float y = float(rand()) / float(RAND_MAX);
		*itr = Particle(x, y);
        //itr->setVx(((float(rand()) / float(RAND_MAX)) - 0.5f) * 0.2f);
        //itr->setVy(((float(rand()) / float(RAND_MAX)) - 0.5f) * 0.2f); 
    }
}

Simulation::~Simulation()
{
    if(!force)
        delete force;
}

void Simulation::setForceGravity(Gravity& g)
{
    if(!force)
        delete force;
    Gravity* gravity = new Gravity();
    *gravity = g;
    force = reinterpret_cast<ForceEmitter*>(gravity);
}

void Simulation::setForceWind(Wind& w)
{
    if(!force)
        delete force;
    Wind* wind = new Wind();
    *wind = w;
    force = reinterpret_cast<ForceEmitter*>(wind);
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

void Simulation::update(const float delta_t)
{
    force->update(delta_t);
    std::vector<Particle>::iterator itr;
    
	for(itr = particles.begin(); itr < particles.end(); itr++)
    {            
        force->apply(*itr, delta_t);
		itr->updatePosition(delta_t);
    }
}

void Simulation::draw(Canvas* canvas)
{
    std::vector<Particle>::iterator itr;
    for(itr = particles.begin(); itr < particles.end(); itr++)
    {
            
        canvas->drawParticle(itr->getX(), itr->getY(),
                         clamp(0.1 / itr->getDistToCOG(), 0.0f, 0.8f) * brightness_modifier,
                         0.5f * brightness_modifier,
                         clamp((1.0 - 0.1 / itr->getDistToCOG()), 0.0f, 1.0f) * brightness_modifier);
    }
	canvas->calcImage();
}
