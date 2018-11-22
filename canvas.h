#pragma once
#include <vector>
#include <cstring>

class Canvas
{
public:
    Canvas();
    
    Canvas(const size_t w, const size_t h);

    void setPointSize(const unsigned int ps);

    unsigned int getPointSize() const;


    void drawPoint(const float x_norm, const float y_norm,
                   const float r, const float g, const float b);

    void clear();

    const unsigned char * const getCanvasData() const;
private:
    size_t width, height, num_pixels;
    unsigned int point_size;
    std::vector<unsigned char> image;
};
