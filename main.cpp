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
    int width = 720, height = 720;    
    GLFWwindow* window = initWindow(width, height);
    if(window)
    {
        initViewport(&viewport);
        //glfwSetMouseButtonCallback(window, mouseButtonCallback);
    }

    Canvas canvas(width, height);
    Simulation sim(10);

    double prev_time = glfwGetTime();
    while(1)
    {
        double current_time = glfwGetTime();
        float delta_t = float(current_time - prev_time);
        sim.update(delta_t);
        sim.draw(canvas);
        displayImage(window, viewport, canvas.getCanvasData(), width, height);
        glfwPollEvents();
        canvas.clear();
        prev_time = current_time;
    }
    
    return 0;
}
