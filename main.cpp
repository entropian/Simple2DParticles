#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>

#include "simulation.h"
#include "gl/glcode.h"
#include "canvas.h"


float calcBrightnessModifier(const int num_particles, const int width, const int height)
{
	const float standard_ratio = 70000.0f / (1080.0f * 1080.0f);
	const int num_pixels = width * height;
	const float particle_pixel_ratio = float(num_particles) / float(num_pixels);
	return logf(standard_ratio / particle_pixel_ratio + 2.f);
}

int main(int argc, char* argv[])
{
	int num_particles;
	if (argc > 1)
	{
		num_particles = atoi(argv[1]);
	}
	else
	{
		num_particles = 100000;
	}
	int width = 1080, height = 1080;
	Viewport viewport(width, height);
	Canvas canvas(width, height);
	float brightness_modifier = calcBrightnessModifier(num_particles, width, height);
    
    Simulation sim(num_particles, 0.05, 0.80, brightness_modifier);
	sim.run(canvas, &viewport);
    return 0;
}
