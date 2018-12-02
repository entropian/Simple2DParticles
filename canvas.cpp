#include <cstring>
#include "canvas.h"

Canvas::Canvas():width(0), height(0), num_pixels(0), point_size(1){}

Canvas::Canvas(const size_t w, const size_t h, const float fade_time):
	width(w), height(h), num_pixels(w * h), point_size(1), fade_time(fade_time)
{
    image.resize(num_pixels * 3 * sizeof(unsigned char));
    std::vector<unsigned char>::iterator itr;
    for(itr = image.begin(); itr != image.end(); itr++)
    {
        *itr = 0;
    }
}

void Canvas::setPointSize(const unsigned int ps)
{
    point_size = ps;
}

unsigned int Canvas::getPointSize() const
{
    return point_size;
}

void Canvas::drawPoint(const float x_norm, const float y_norm,
               const float r, const float g, const float b)
{
    int x = x_norm * width;
    int y = y_norm * height;

    if((x >= 0 && x < width) &&
       (y > 0 && y <= height))
    {
        unsigned int index = (height - y) * width + x;
        unsigned char value;
        value = image[index*3] + (unsigned char)(r * 255.0f);
        image[index*3] = image[index*3] > value ? 255 : value;
        value = image[index*3+1] + (unsigned char)(g * 255.0f);
        image[index*3+1] = image[index*3+1] > value ? 255 : value;
        value = image[index*3+2] + (unsigned char)(b * 255.0f);
        image[index*3+2] = image[index*3+2] > value ? 255 : value;            
    }else
    {
        //fprintf(stderr, "Invalid coordiate (%d, %d)\n", x, y);
    }
}

void Canvas::clear()
{
    // NOTE: In speed: memset > for loop with an index > iterator
    memset(&(image[0]), 0, num_pixels * 3 * sizeof(unsigned char));
}

void Canvas::fade(const float delta_t)
{
	if (fade_time == 0)
	{
		clear();
		return;
	}
	const float fade_per_sec = 1.f / fade_time;
	const float fade_val = fade_per_sec * delta_t;
	for (int i = 0; i < num_pixels; i++)
	{
		unsigned char r, g, b;
		r = image[i * 3];
		g = image[i * 3 + 1];
		b = image[i * 3 + 2];
		if (r == g && g == b && b == 0)
			continue;
		float max_comp;
		if (r > g && r > b)
		{
			max_comp = float(r);
		}
		else if (g > b)
		{
			max_comp = float(g);
		}
		else
		{
			max_comp = float(b);
		}
		for (int j = 0; j < 3; j++)
		{
			float val = float(image[i * 3 + j]);
			float scaling = val / max_comp;
			unsigned char reduction = fade_val * 255.0f * scaling;
			unsigned char final_val = image[i * 3 + j] - reduction;
			if (final_val > image[i * 3 + j])
				image[i * 3 + j] = 0;
			else
				image[i * 3 + j] = final_val;
		}
	}
}

const unsigned char * const Canvas::getCanvasData() const
{
    return &(image[0]);
}                    

size_t Canvas::getWidth() const
{
	return width;
}

size_t Canvas::getHeight() const
{
	return height;
}