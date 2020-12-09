#pragma once

// #include "explosion.hpp"
// #include "fireworks.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

class Rocket {
    public:
        Rocket(float x, float y, float z, float height)
            : x(x), y(y), z(z), height(height) {
                isExploded = false;
                color = new float[3];
            }
        ~Rocket() {
            delete [] color;
        }

        void bindObjects(GLuint cone, GLuint stem) {
            this->cone = cone;
            this->stem = stem;
        }

        void accelerate(float velocity) {
            if (velocity > 0) {
                y += velocity;
            } else {
                //isExploded = true;
            }
        }

        void setColor(float r, float g, float b) {
            color[0] = r;
            color[1] = g;
            color[2] = b;
        }

        void drawRocket() {
            
            // this is the rocket portion
            glPushMatrix();
                glColor3f(color[0], color[1], color[2]);
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

    private:
        float x, y, z;
        float height;
        GLuint cone, stem;
        float *color;
        bool isExploded;
};