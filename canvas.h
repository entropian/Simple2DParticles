#pragma once
#include <vector>
#include <cstring>

class Canvas
{
public:
    Canvas();
    
    Canvas(const size_t w, const size_t h, const float fade_time = 0.0f);
    void setPointSize(const unsigned int ps);
    unsigned int getPointSize() const;
    void drawParticle(const float x_norm, const float y_norm,
                   const float r, const float g, const float b);
    void clear();
	void fade(const float delta_t);
    const unsigned char * const getCanvasData() const;
	size_t getWidth() const;
	size_t getHeight() const;

private:
	void drawPoint(const int x, const int y, const float r, const float g, const float b);

    size_t width, height, num_pixels;
    unsigned int point_size;
    std::vector<unsigned char> image;
	float fade_time;
};
