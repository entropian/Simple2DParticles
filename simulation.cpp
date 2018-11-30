#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "simulation.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

static float clamp(const float a, const float b, const float c)
{
    if(a < b)
    {
        return b;
    }
    if(a > c)
    {
        return c;
    }
    return a;
}

Simulation::Simulation(const int num_particles, const float orbit_radius, const float damping,
           const float brightness_modifier)
    :orbit_radius(orbit_radius), damping(damping), time(0), brightness_modifier(brightness_modifier)
{
    particles.resize(num_particles);
    srand(0);
    std::vector<Particle>::iterator itr;
    for(itr = particles.begin(); itr < particles.end(); itr++)
    {
        itr->setX(float(rand()) / float(RAND_MAX));
        itr->setY(float(rand()) / float(RAND_MAX));
        //itr->setVx(((float(rand()) / float(RAND_MAX)) - 0.5f) * 0.2f);
        //itr->setVy(((float(rand()) / float(RAND_MAX)) - 0.5f) * 0.2f);
        itr->setVx(0);
        itr->setVy(0);            
    }
}

static const double display_time_interval = 1.0;

void Simulation::run(Canvas& canvas, GLFWwindow* window, const GlViewport* viewport)
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
		draw(canvas);
		displayImage(window, viewport, canvas.getCanvasData(), canvas.getWidth(), canvas.getHeight());
		if (current_time - last_display_time >= display_time_interval)
		{
			std::cout << 1.0f / delta_t << " FPS\n";
			last_display_time = current_time;
		}
		glfwPollEvents();
		canvas.clear();
		prev_time = current_time;
	}
}

void Simulation::update(const float delta_t)
{
    float cog_x = cos(time) * orbit_radius + 0.5f;
    float cog_y = sin(time) * orbit_radius + 0.5f;
    time += delta_t;
    std::vector<Particle>::iterator itr;
    for(itr = particles.begin(); itr < particles.end(); itr++)
    {            
        itr->updatePosition(delta_t, cog_x, cog_y, damping);
    }
}

void Simulation::draw(Canvas& canvas)
{
    std::vector<Particle>::iterator itr;
    for(itr = particles.begin(); itr < particles.end(); itr++)
    {
            
        canvas.drawPoint(itr->getX(), itr->getY(),
                         clamp(0.1 / itr->getDistToCOG(), 0.0f, 0.8f) * brightness_modifier,
                         0.5f * brightness_modifier,
                         clamp((1.0 - 0.1 / itr->getDistToCOG()), 0.0f, 1.0f) * brightness_modifier);
    }
}
