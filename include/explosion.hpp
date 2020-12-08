#pragma once

#include "rocket.hpp"

class Explosion {
    public:
        Explosion(int numParticles) 
            : numParticles(numParticles) {}

        ~Explosion();

        
    private:
        int numParticles;
};