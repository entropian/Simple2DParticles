#pragma once
#include <cstdio>

struct GlViewport;
struct GLFWwindow;

GlViewport* initViewport();

GLFWwindow* initWindow(unsigned int width, unsigned int height);

void displayImage(GLFWwindow* window, const GlViewport* viewport,
	const unsigned char* image, int width, int height);
