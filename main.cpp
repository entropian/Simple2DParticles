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

    Simulation sim(num_particles, brightness_modifier);
    Gravity gravity1(0.3f, 0.7f, 0.05f);
	Gravity gravity2(0.7f, 0.3f, 0.05f);
    Wind wind(1.0f, 0.0f, 0.01f);
    sim.addForceGravity(gravity1);
	sim.addForceGravity(gravity2);
    //sim.addForceWind(wind);
	sim.run(&canvas, &viewport);
    return 0;
}
