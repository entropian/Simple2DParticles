#pragma once

struct GlViewport;
struct GLFWwindow;

class Viewport
{
public:
	Viewport(const int width, const int height);
	void initViewport();
	void initWindow(const int width, const int height);
	void displayImage(const unsigned char* image, const int width, const int height);

private:
	GlViewport* viewport;
	GLFWwindow* window;
};