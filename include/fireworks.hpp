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
                rocket = new Rocket(x, y, z);
                explosion = new Explosion(10); // set the explosion to have 10 particles
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
                explosion->setOriginPoint(x, y, z);
                explosion->setOriginTime(t);
            }
            
            if (exploded) {

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

        float x, y, z;
        unsigned char rgb[3];
        bool exploded;
};