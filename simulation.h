#pragma once
//#include <random>
#include <stdlib.h>
#include <vector>
#include "particle.h"
#include "canvas.h"
#include <iostream>

class Simulation
{
public:
    Simulation(const int num_particles)
    {
        particles.resize(num_particles);
        srand(0);
        std::vector<Particle>::iterator itr;
        int count = 0;
        for(itr = particles.begin(); itr < particles.end(); itr++)
        {
            std::cout << count << "\n";
            count++;
            itr->setX(float(rand()) / float(RAND_MAX));
            itr->setY(float(rand()) / float(RAND_MAX));
            //itr->setVx((float(rand()) / float(RAND_MAX)) - 0.5f);
            //itr->setVy((float(rand()) / float(RAND_MAX)) - 0.5f);
            itr->setVx(0);
            itr->setVy(0);            
        }
        cog_x = 0.5f;
        cog_y = 0.5f;
    }

    void update(const float delta_t)
    {
        std::vector<Particle>::iterator itr;
        for(itr = particles.begin(); itr < particles.end(); itr++)
        {            
            itr->updatePosition(delta_t, cog_x, cog_y);
        }
    }

    void draw(Canvas& canvas)
    {
        std::vector<Particle>::iterator itr;
        for(itr = particles.begin(); itr < particles.end(); itr++)
        {
            canvas.drawPoint(itr->getX(), itr->getY(), 1.0f, 1.0f, 1.0f);
        }        
    }
private:
    std::vector<Particle> particles;
    float cog_x, cog_y; // Center of gravity
};
