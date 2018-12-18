#pragma once

struct GlViewport;
struct GLFWwindow;

class Viewport
{
public:
	Viewport(const int width, const int height);
	void initViewport(const float aspect_ratio);
	void initWindow(const int width, const int height);
	void displayImage(const unsigned char* image, const int width, const int height);
	GLFWwindow* getWindow();
private:
	GlViewport* viewport;
	GLFWwindow* window;
};