#pragma once

// #include "explosion.hpp"
// #include "fireworks.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "lighting.hpp"

class Rocket {
    public:
        Rocket(float x, float y, float z)
            : x(x), y(y), z(z) {
                isExploded = false;
                color = new float[3];
            }
        ~Rocket() {
            delete [] color;
        }

        float getX() { return x; }

        float getY() { return y; }

        float getZ() { return z; }

        void bindObjects(GLuint cone, GLuint stem) {
            this->cone = cone;
            this->stem = stem;
        }

        void accelerate(float velocity) {
            if (velocity > 0) {
                y += velocity;
            }
        }

        void setColor(float r, float g, float b) {
            color[0] = r;
            color[1] = g;
            color[2] = b;
        }

        void drawRocket() {
            
            SetPointLight(GL_LIGHT1, x, y + 0.8, z, .5, .5, .5);

            // this is the rocket portion
            glPushMatrix();
                SetMaterial(color[0], color[1], color[2], 1.);
                glTranslatef(x, y, z);
                glScalef(1.5, 1.5, 1.5);
                glCallList(cone);
            glPopMatrix();

            // this is the stem portion
            glPushMatrix();
                SetMaterial(1., 1., 1., 1.);
                glTranslatef(x, y, z);
                glScalef(1.5, 1.5, 1.5);
                glCallList(stem);
            glPopMatrix();
        }

    private:
        float x, y, z;
        GLuint cone, stem;
        float *color;
        bool isExploded;
};