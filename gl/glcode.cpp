#include "glcode.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glshaders.h"
#include <cstdio>


struct GlViewport
{
	GLuint vao, vbo, textureHandle, shaderProgram;
};

void GlViewportDeleter::operator()(GlViewport *v)
{
	delete v;
}

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

	if (status != GL_TRUE)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "Vertex shader compiled incorrectly.\n");
		fprintf(stderr, "%s\n", infoLog);
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
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
	if (status != GL_TRUE)
	{
		glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Shaders linked incorrectly.\n");
		fprintf(stderr, "%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


Viewport::Viewport(const int width, const int height)
{
	// Init GLFW
	if (glfwInit() != GL_TRUE)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}
	viewport.reset(new GlViewport);
	initWindow(width, height);
	if (window)
	{
		initViewport(float(width) / float(height));
		//glfwSetMouseButtonCallback(window, mouseButtonCallback);
		ImGui_ImplGlfwGL3_Init(window.get(), true);
	}
}

Viewport::~Viewport()
{
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
}

void Viewport::initViewport(const float aspect_ratio)
{
	viewport.reset(new GlViewport);
	readAndCompileShaders(basicVertSrc, basicFragSrc, &(viewport->shaderProgram));
	glUseProgram(viewport->shaderProgram);

	float h_extent = 1.0f / aspect_ratio * 2.0f;

	GLfloat vertices[] = {
		1.0f-h_extent,  -1.0f, 0.0f, 0.0f,
		1.0f-h_extent, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, -1.0, 1.0f, 0.0f,
		1.0f-h_extent, 1.0, 0.0f, 1.0f,
		1.0f, 1.0, 1.0f, 1.0f
	};

	//GLfloat vertices[] = {
	//-1.0f,  -1.0f, 0.0f, 0.0f,
	//-1.0f, 1.0f, 0.0f, 1.0f,
	//1.0f, -1.0f, 1.0f, 0.0f,
	//1.0, -1.0, 1.0f, 0.0f,
	//-1.0, 1.0, 0.0f, 1.0f,
	//1.0, 1.0, 1.0f, 1.0f
	//};

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
void Viewport::initWindow(const int width, const int height)
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

	window.reset(glfwCreateWindow(width, height, "Particles", NULL, NULL));
	glfwSetWindowPos(window.get(), 600, 100);
	glfwMakeContextCurrent(window.get());

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
}

void Viewport::displayImage(const unsigned char* image, int width, int height)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	ImGui::Render();
	glfwSwapBuffers(window.get());
}

GLFWwindow* Viewport::getWindow()
{
	return window.get();
}

void GLFWwindowDeleter::operator()(GLFWwindow *w)
{
	delete w;
}