#pragma once
#include <cstdio>

struct GlViewport;
struct GLFWwindow;

GlViewport* initViewport();

GLFWwindow* initWindow(unsigned int width, unsigned int height);

void displayImage(GLFWwindow* window, const GlViewport* viewport,
	const unsigned char* image, int width, int height);


class Viewport
{
public:
	Viewport(const size_t width, const size_t height);
	void initViewport();
	void initWindow(const size_t width, const size_t height);
	void displayImage(const unsigned char* image, const int width, const int height);
	GlViewport* getViewport()
	{
		return viewport;
	}
	GLFWwindow* getWindow()
	{
		return window;
	}
private:
	GlViewport* viewport;
	GLFWwindow* window;
};