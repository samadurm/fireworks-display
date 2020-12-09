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
                explosion->setOriginPoint(rocket->getX(), rocket->getY(), rocket->getZ());
                explosion->setOriginTime(t);
            }
            
            if (exploded) {
                explosion->updateParticles(t);
            } else {
                rocket->accelerate(v);
            }
        }

        void drawFireworks(float time) {
            if (exploded) { 
                explosion->drawParticles(time);
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