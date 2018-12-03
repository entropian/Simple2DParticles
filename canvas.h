#pragma once
#include <vector>
#include <cstring>

class Canvas
{
public:
    Canvas();
    
    Canvas(const size_t w, const size_t h, const int particle_size = 0, const float fade_time = 0.0f);
    void setPointSize(const unsigned int ps);
    unsigned int getPointSize() const;
    void drawParticle(const float x_norm, const float y_norm,
                   const float r, const float g, const float b);
    void clear();
	void fade(const float delta_t);
    const unsigned char * const getCanvasData() const;
	size_t getWidth() const;
	size_t getHeight() const;
	void mergeBuffers();
	void clearNewImage();
private:
	void drawPoint(const int x, const int y, const float r, const float g, const float b);
	void clearDrawn();


    size_t width, height, num_pixels;
    unsigned int point_size;
    std::vector<unsigned char> image;
	std::vector<unsigned char> new_image;
	std::vector<bool> drawn;
	float fade_time;
};
