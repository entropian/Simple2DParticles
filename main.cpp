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
	auto width = 1080, height = 1080;
	Viewport viewport(width, height);
	Canvas canvas(width, height, 0, 0.0f);
	auto brightness_modifier = calcBrightnessModifier(num_particles, width, height);

    Simulation sim(num_particles, brightness_modifier);
    Gravity gravity1(0.3f, 0.7f, 0.05f);
	Gravity gravity2(0.7f, 0.3f, 0.0f);
    Wind wind(1.0f, 0.0f, 0.00005f);

    sim.addForceGravity(gravity1);
	sim.addForceGravity(gravity2);
    sim.addForceWind(wind);
	sim.addParticleEmitter(0.15f, 0.15f, 1000.0f);
	sim.addParticleEmitter(0.15, 0.75f, 500.0f);

	sim.run(&canvas, &viewport);
    return 0;
}
