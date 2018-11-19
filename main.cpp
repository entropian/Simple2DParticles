#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "gl/glcode.h"


int main()
{
    // Init GLFW
    if(glfwInit() != GL_TRUE)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
    }
    GlViewport viewport;
    GLFWwindow* window = initWindow(1280, 720);
    if(window)
    {
        initViewport(&viewport);
        //glfwSetMouseButtonCallback(window, mouseButtonCallback);
    }

    //float* color_buffer = NULL;
    int width = 1280, height = 720;

    int num_pixels = width * height;
    unsigned char* image = (unsigned char*)malloc(num_pixels * 3 * sizeof(unsigned char));
    for(int i = 0; i < num_pixels; i+=3)
    {
        image[i*3] = 255;
        image[i*3+1] = 0;
        image[i*3+2] = 0;
    }

    while(1)
    {
        displayImage(window, viewport, image, width, height);
        glfwPollEvents();
    }
    
    return 0;
}
