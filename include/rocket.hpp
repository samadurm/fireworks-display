#pragma once

// #include "explosion.hpp"
// #include "fireworks.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

class Rocket {
    public:
        Rocket(float velocity, float x, float y, float z, GLuint cone, GLuint stem)
            : velocity(velocity), x(x), y(y), z(z), cone(cone), stem(stem) {
                height = 0.2;
            }
        ~Rocket() {}

        void drawRocket() {
            glPushMatrix();
                glTranslatef(x, y, z);
                glRotatef(-90., 1., 0., 0.);
                glCallList(cone);
            glPopMatrix();

            glPushMatrix();
                glColor3f(1., 1., 1.);
                glTranslatef(x, y, z);
                glCallList(stem);
            glPopMatrix();
        }
        
    private:
        float velocity, x, y, z;
        float height;
        GLuint cone, stem;
};