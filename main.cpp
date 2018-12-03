#include "simulation.h"
#include "gl/glcode.h"
#include "canvas.h"
#include "util.h"
#include "platform.h"
#include <iostream>

int main(int argc, char* argv[])
{
#ifdef _WIN32
	// Restricts process to CPU 1, because core switching causes jitter
	setAffinity();
#endif
	int num_particles = 70000;
	if (argc > 1)
	{
		num_particles = atoi(argv[1]);
	}
	int width = 1080, height = 1080;
	Viewport viewport(width, height);
	Canvas canvas(width, height, 0, 0.0f);
	float brightness_modifier = calcBrightnessModifier(num_particles, width, height);
    
    Simulation sim(num_particles, 0.05, 0.80, brightness_modifier);
	sim.run(&canvas, &viewport);
    return 0;
}
