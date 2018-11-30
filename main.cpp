#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>

#define GLCODE_IMPLEMENTATION
#include "gl/glcode.h"

#include "canvas.h"
#include "simulation.h"

const float standard_ratio = 70000.0f / (1080.0f * 1080.0f);

int main()
{
    // Init GLFW
    if(glfwInit() != GL_TRUE)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
    }
    GlViewport viewport;
    int width = 1080, height = 1080;    
    GLFWwindow* window = initWindow(width, height);
    if(window)
    {
        initViewport(&viewport);
        //glfwSetMouseButtonCallback(window, mouseButtonCallback);
    }
    
    Canvas canvas(width, height);
    const int num_particles = 500000;
    const int num_pixels = width * height;
    const float particle_pixel_ratio = float(num_particles) / float(num_pixels);
    float brightness_modifier = logf(standard_ratio / particle_pixel_ratio + 2.f);
    
    Simulation sim(num_particles, 0.05, 0.80, brightness_modifier);

	sim.run(canvas, window, &viewport);
    return 0;
}
