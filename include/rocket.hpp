#pragma once

// #include "explosion.hpp"
// #include "fireworks.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

class Rocket {
    public:
        Rocket(float velocity, float x, float y, float z)
            : velocity(0.1), x(x), y(y), z(z) {
                height = 0.2;
                isExploded = false;
            }
        ~Rocket() {}

        void bindObjects(GLuint cone, GLuint stem) {
            this->cone = cone;
            this->stem = stem;
        }

        // void move(float amount) {
        //     this->y += amount;
        // }

        void accelerate(const float g) {
            if (velocity > 0) {
                velocity -= g;
                y += velocity;
                printf("Velocity is now %f and y is %f\n", velocity, y);
            } else if (velocity < 0) {
                velocity = 0;
                isExploded = true;
            }
        }

        void drawFireworks() {
            if (isExploded) {
                drawExplosion();
            } else {
                drawRocket();
            }
        }

        void setColor(const GLfloat *color) {
            this->color = *color;
        }

    private:
        void drawRocket() {
            
            // this is the rocket portion
            glPushMatrix();
                glColor3fv(&color);
                glTranslatef(x, y, z);
                glRotatef(-90., 1., 0., 0.);
                glCallList(cone);
            glPopMatrix();

            // this is the stem portion
            glPushMatrix();
                glColor3f(1., 1., 1.);
                glTranslatef(x, y, z);
                glCallList(stem);
            glPopMatrix();
        }

        void drawExplosion() {
            printf("Rocket has exploded, must draw fireworks");
        }
        

        float velocity, x, y, z;
        float height;
        GLuint cone, stem;
        GLfloat color;
        bool isExploded;
};