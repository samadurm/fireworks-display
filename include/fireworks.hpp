#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

#include "explosion.hpp"
#include "rocket.hpp"

class Fireworks {

    public:

        Fireworks(float x, float y, float z) 
            : x(x), y(y), z(z) {
                rocketHeight = 0.2;
                rocket = new Rocket(x, y, z, rocketHeight);
                explosion = new Explosion(20); // set the explosion to have 10 particles
                exploded = false;
            }
        ~Fireworks() {}

        void bindObjects(GLuint cone, GLuint stem, GLuint particle) {
            rocket->bindObjects(cone, stem);
            explosion->bindParticles(particle);
        }

        void processMovement(float v, float t) {
            
            if (v == 0. && !exploded) {
                exploded = true;
                explosion->setOriginPoint(x, y+rocketHeight + 1, z);
                explosion->setOriginTime(t);
            }
            
            if (exploded) {
                explosion->updateParticles(t);
            } else {
                printf("v is %f\n", v);
                rocket->accelerate(v);
            }
        }

        void drawFireworks() {
            if (exploded) { 
                explosion->drawParticles();
            } else {
                rocket->drawRocket();
            }
        }

        void setColor(float r, float g, float b) {
            rocket->setColor(r, g, b);
            explosion->setColor(r, g, b);
        }

    private:
        Rocket *rocket;
        Explosion *explosion;

        float x, y, z, rocketHeight;
        unsigned char rgb[3];
        bool exploded;
};