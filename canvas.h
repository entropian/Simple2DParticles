#include <vector>

class Canvas
{
public:
    Canvas():width(0), height(0), num_pixels(0), point_size(1){}
    Canvas(const size_t w, const size_t h):width(w), height(h), num_pixels(w * h), point_size(1)
    {
        image.reserve(num_pixels * 3 * sizeof(unsigned char));
        std::vector<unsigned char>::iterator itr;
        for(itr = image.begin(); itr != image.end(); itr++)
        {
            *itr = 0;
        }
    }

    void setPointSize(const unsigned int ps)
    {
        point_size = ps;
    }

    unsigned int getPointSize() const
    {
        return point_size;
    }

    void drawPoint(const float x_norm, const float y_norm,
                   const float r, const float g, const float b)
    {
        int x = x_norm * width;
        int y = y_norm * height;
        if((x >= 0 && x < width) &&
           (y >= 0 && y < height))
        {
            unsigned int index = (height - y) * width + x;
            image[index*3] = (unsigned char)(r * 255.0f);
            image[index*3 + 1] = (unsigned char)(g * 255.0f);
            image[index*3 + 2] = (unsigned char)(b * 255.0f);
        }else
        {
            fprintf(stderr, "Invalid coordiate (%d, %d)\n", x, y);
        }
    }

    void clear()
    {
        std::vector<unsigned char>::iterator itr;
        for(itr = image.begin(); itr != image.end(); itr++)
        {
            *itr = 0;
        }
        for(int i = 0; i < num_pixels; i++)
        {
            image[i*3] = 0;
            image[i*3+1] = 0;
            image[i*3+2] = 0;
        }
    }

    const unsigned char * const getCanvasData() const
    {
        return &(image[0]);
    }                    
private:
    size_t width, height, num_pixels;
    unsigned int point_size;
    std::vector<unsigned char> image;
};
