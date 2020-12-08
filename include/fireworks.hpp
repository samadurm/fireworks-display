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
                // explosion = new Explosion(10); // set the explosion to have 10 particles
                exploded = false;
            }
        ~Fireworks() {}

        void bindRocket(GLuint cone, GLuint stem) {
            rocket->bindObjects(cone, stem);
        }

        void processMovement(float v, float t) {
            
            if (v == 0. && !exploded) {
                exploded = true;
                // explosion->setOriginPoint(x, y, z);
            }
            
            if (exploded) {

            } else {
                printf("v is %f\n", v);
                rocket->accelerate(v);
            }
        }

        void drawFireworks() {
            if (exploded) { 
                
            } else {
                rocket->drawFireworks();
            }
        }

        void setColor(const GLfloat *color) {
            this->color = *color;
            rocket->setColor(color);
        }

    private:
        Rocket *rocket;
        Explosion *explosion;
        GLfloat color;

        float x, y, z;
        unsigned char rgb[3];
        bool exploded;
};