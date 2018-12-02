#pragma once

struct GlViewport;
struct GLFWwindow;

class Viewport
{
public:
	Viewport(const size_t width, const size_t height);
	void initViewport();
	void initWindow(const size_t width, const size_t height);
	void displayImage(const unsigned char* image, const int width, const int height);

private:
	GlViewport* viewport;
	GLFWwindow* window;
};