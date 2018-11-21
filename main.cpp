#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "gl/glcode.h"
#include "canvas.h"
#include "simulation.h"

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
    Simulation sim(150000, 0.05, 0.80);

    const double display_time_interval = 1.0;
    double prev_time = glfwGetTime();
    double last_display_time = prev_time;
    while(1)
    {
        double current_time = glfwGetTime();
        float delta_t = float(current_time - prev_time);
        sim.update(delta_t);
        sim.draw(canvas);
        displayImage(window, viewport, canvas.getCanvasData(), width, height);
        if(current_time - last_display_time >= display_time_interval)
        {
            std::cout << 1.0f / delta_t << " FPS\n";
            last_display_time = current_time;
        }
        glfwPollEvents();
        canvas.clear();
        prev_time = current_time;
    }
    
    return 0;
}
