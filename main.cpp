#include "simulation.h"
#include "gl/glcode.h"
#include "canvas.h"
#include "util.h"

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
	sim.run(&canvas, &viewport);
    return 0;
}
