#include <cstring>
#include <algorithm>
#include "canvas.h"

Canvas::Canvas():width(0), height(0), num_pixels(0), point_size(1){}

Canvas::Canvas(const int w, const int h, const int particle_size, const float fade_time):
	width(w), height(h), num_pixels(w * h), point_size(particle_size), fade_time(fade_time)
{
    image.resize(num_pixels * 3);
	for(auto &c : image)
    {
        c = 0;
    }
	if (fade_time > 0.0f)
	{
		draw_buffer.resize(num_pixels * 3);
		for(auto &c : draw_buffer)
		{
			c = 0;
		}
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
void Canvas::drawParticle(const float x_norm, const float y_norm,
	const float r, const float g, const float b)
{
    int x = x_norm * width;
    int y = y_norm * height;

	std::vector<unsigned char>* buffer;
	if (fade_time > 0.0f)
		buffer = &draw_buffer;
	else
		buffer = &image;
	
	if (point_size == 0)
	{
		drawPoint(buffer, x, y, r, g, b);
	}
	else if (point_size == 1)
	{
		auto outer = 0.5f;
		auto inner = 0.8f;

		drawPoint(buffer, x - 1, y - 1, r*outer, g*outer, b*outer);
		drawPoint(buffer, x - 0, y - 1, r*inner, g*inner, b*inner);
		drawPoint(buffer, x + 1, y - 1, r*outer, g*outer, b*outer);

		drawPoint(buffer, x - 1, y - 0, r*inner, g*inner, b*inner);
		drawPoint(buffer, x - 0, y - 0, r, g, b);
		drawPoint(buffer, x + 1, y - 0, r*inner, g*inner, b*inner);

		drawPoint(buffer, x - 1, y + 1, r*outer, g*outer, b*outer);
		drawPoint(buffer, x - 0, y + 1, r*inner, g*inner, b*inner);
		drawPoint(buffer, x + 1, y + 1, r*outer, g*outer, b*outer);
	}
	
}

void Canvas::drawPoint(std::vector<unsigned char>* buffer,
	const int x, const int y, const float r, const float g, const float b)
{
	if ((x >= 0 && x < width) &&
		(y > 0 && y <= height))
	{
		unsigned int index = (height - y) * width + x;

		unsigned char value;
		value = (*buffer)[index * 3] + (unsigned char)(r * 255.0f);
		(*buffer)[index * 3] = (*buffer)[index * 3] > value ? 255 : value;
		value = (*buffer)[index * 3 + 1] + (unsigned char)(g * 255.0f);
		(*buffer)[index * 3 + 1] = (*buffer)[index * 3 + 1] > value ? 255 : value;
		value = (*buffer)[index * 3 + 2] + (unsigned char)(b * 255.0f);
		(*buffer)[index * 3 + 2] = (*buffer)[index * 3 + 2] > value ? 255 : value;
	}
}

void Canvas::calcImage()
{
	if (fade_time > 0.0f)
	{
		for (int i = 0; i < num_pixels * 3; i++)
		{
			image[i] = image[i] > draw_buffer[i] ? image[i] : draw_buffer[i];
		}
	}
}

void Canvas::clearImageBuffer()
{
    // NOTE: In speed: memset > for loop with an index > iterator
    memset(&(image[0]), 0, num_pixels * 3 * sizeof(unsigned char));
}

void Canvas::clearDrawBuffer()
{
	memset(&(draw_buffer[0]), 0, num_pixels * 3 * sizeof(unsigned char));
}

void Canvas::fade(const float delta_t)
{
	if (fade_time == 0)
	{
		clearImageBuffer();
		return;
	}
	const auto fade_per_sec = 1.f / fade_time;
	const auto fade_val = fade_per_sec * delta_t;
	for (int i = 0; i < num_pixels; i++)
	{
		auto r = image[i * 3];
		auto g = image[i * 3 + 1];
		auto b = image[i * 3 + 2];
		if (r == g && g == b && b == 0)
			continue;
		float max_comp = std::max(r, std::max(g, b));
		for (int j = 0; j < 3; j++)
		{
			auto val = float(image[i * 3 + j]);
			auto scaling = val / max_comp;
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

int Canvas::getWidth() const
{
	return width;
}

int Canvas::getHeight() const
{
	return height;
}

void Canvas::prepDrawing(const float delta_t)
{
	if (fade_time > 0)
	{
		fade(delta_t);
		clearDrawBuffer();
	}
	else
		clearImageBuffer();
}