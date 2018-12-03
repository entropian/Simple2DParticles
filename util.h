#include <cmath>

static float clamp(const float a, const float b, const float c)
{
	if (a < b)
	{
		return b;
	}
	if (a > c)
	{
		return c;
	}
	return a;
}


static float calcBrightnessModifier(const int num_particles, const int width, const int height)
{
	const float standard_ratio = 70000.0f / (1080.0f * 1080.0f);
	const int num_pixels = width * height;
	const float particle_pixel_ratio = float(num_particles) / float(num_pixels);
	float brightness_modifier = logf(standard_ratio / particle_pixel_ratio + 2.f);
	return clamp(brightness_modifier, 0.0f, 1.0f);
}