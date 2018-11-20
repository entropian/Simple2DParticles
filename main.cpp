#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "gl/glcode.h"
#include "canvas.h"
#include "particle.h"

int main()
{
    // Init GLFW
    if(glfwInit() != GL_TRUE)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
    }
    GlViewport viewport;
    GLFWwindow* window = initWindow(720, 720);
    if(window)
    {
        initViewport(&viewport);
        //glfwSetMouseButtonCallback(window, mouseButtonCallback);
    }

    int width = 720, height = 720;
    Canvas canvas(width, height);

    Particle p(500.0f/width, 400.0f/width, 0.1f, 0.1f);

    double prev_time = glfwGetTime();
    while(1)
    {
        double current_time = glfwGetTime();
        float delta_t = float(current_time - prev_time);
        p.updatePosition(delta_t);
        canvas.drawPoint(p.getX(), p.getY(), 1.0f, 1.0f, 1.0f);
        displayImage(window, viewport, canvas.getCanvasData(), width, height);
        glfwPollEvents();
        canvas.clear();
        prev_time = current_time;
    }
    
    return 0;
}
