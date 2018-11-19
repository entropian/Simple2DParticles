#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include "glshaders.h"

struct GlViewport
{
    GLuint vao, vbo, textureHandle, shaderProgram;
};

// Compile the shaders and link the program
void readAndCompileShaders(const char *vs, const char *fs, GLuint *shaderProgram)
{
    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, NULL);
    glCompileShader(vertexShader);

    GLint status;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "Vertex shader compiled incorrectly.\n");
        fprintf(stderr, "%s\n", infoLog);
    }
        
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "Fragment shader compiled incorrectly.\n");
        fprintf(stderr, "%s\n", infoLog);
    }

    // Link the vertex and fragment shader into the shader program
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glBindFragDataLocation(*shaderProgram, 0, "outColor");
    glLinkProgram(*shaderProgram);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "Shaders linked incorrectly.\n");
        fprintf(stderr, "%s\n", infoLog);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void initViewport(GlViewport *viewport)
{
    readAndCompileShaders(basicVertSrc, basicFragSrc, &(viewport->shaderProgram));
    glUseProgram(viewport->shaderProgram);

    GLfloat vertices[] = {
        -1.0f,  -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,        
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0, -1.0, 1.0f, 0.0f,
        -1.0, 1.0, 0.0f, 1.0f,
        1.0, 1.0, 1.0f, 1.0f
    };    


    glGenVertexArrays(1, &(viewport->vao));
    glBindVertexArray(viewport->vao);

    glGenBuffers(1, &viewport->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, viewport->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(viewport->shaderProgram, "aPosition");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    GLint texAttrib = glGetAttribLocation(viewport->shaderProgram, "aTexcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));    
    

    //------------------- Texture
    glGenTextures(1, &(viewport->textureHandle));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, viewport->textureHandle);
    
    // NOTE: implement antialiasing and filtering?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint textureUniform = glGetUniformLocation(viewport->shaderProgram, "textureMap");
    glUniform1i(textureUniform, 0);    
}

GLFWwindow* initWindow(unsigned int width, unsigned int height)
{
    /*
    // Init GLFW
    if(glfwInit() != GL_TRUE)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
        //return -1;
    }
    */
    // Create a rendering window with OpenGL 3.2 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, "CRaytracer", NULL, NULL);
    glfwSetWindowPos(window, 600, 100);
    glfwMakeContextCurrent(window);

    // Init GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return NULL;
    }
    return window;
}

void displayImage(GLFWwindow* window, const GlViewport viewport,
                  const unsigned char* image, int width, int height)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);    


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwSwapBuffers(window);
}
