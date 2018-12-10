#include "simulation.h"
#include "gl/glcode.h"
#include "canvas.h"
#include "util.h"
#include "platform.h"
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


int main(int argc, char* argv[])
{
#ifdef _WIN32
	// Restricts process to CPU 1, because core switching causes jitter
	setAffinity();
#endif
	auto num_particles = 70000;
	if (argc > 1)
	{
		num_particles = atoi(argv[1]);
	}
	auto height = 1080, width = int(float(height) * 1.25f);
	Viewport viewport(width, height);
	Canvas canvas(height, height, 0, 0.0f); // Square canvas
	auto brightness_modifier = calcBrightnessModifier(70000, height, height);

    Simulation sim(num_particles, brightness_modifier);
    Gravity gravity1(0.3f, 0.7f, 0.05f);
	Gravity gravity2(0.7f, 0.3f, 0.0f);
    Wind wind(1.0f, 0.0f, 0.00005f);

    sim.addForceGravity(gravity1);
	sim.addForceGravity(gravity2);
    sim.addForceWind(wind);
	sim.addParticleEmitter(0.15f, 0.15f, 1000.0f);
	sim.addParticleEmitter(0.15, 0.75f, 500.0f);

	ImGui_ImplGlfwGL3_Init(viewport.getWindow(), true);

	sim.run(&canvas, &viewport);

	ImGui_ImplGlfwGL3_Shutdown();
    return 0;
}
