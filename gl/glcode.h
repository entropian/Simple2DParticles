#pragma once
#include <memory>

struct GlViewport;
struct GlViewportDeleter
{
	void operator()(GlViewport *v);
};

struct GLFWwindow;
struct GLFWwindowDeleter
{
	void operator()(GLFWwindow *w);
};

class Viewport
{
public:
	Viewport(const int width, const int height);
	~Viewport();
	void initViewport(const float aspect_ratio);
	void initWindow(const int width, const int height);
	void displayImage(const unsigned char* image, const int width, const int height);
	GLFWwindow* getWindow();
private:
	std::unique_ptr<GlViewport, GlViewportDeleter> viewport;
	std::unique_ptr<GLFWwindow, GLFWwindowDeleter> window;
};