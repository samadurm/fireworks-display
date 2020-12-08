#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

class Explosion {
    public:
        Explosion(int numParticles) 
            : numParticles(numParticles) {
                color = new float[3];
            }

        ~Explosion() {
            delete [] color;
        };
        
        void bindParticles(GLuint particle) {
            this->particleList = particle;
        }

        void setColor(float r, float g, float b) {
            color[0] = r;
            color[1] = g;
            color[2] = b;
        }

        void setOriginPoint(float x, float y, float z) {
            originX = x;
            originY = y;
            originZ = z;
            radius = 0.2;
        }

        void setOriginTime(float time) {
            originTime = time;
            endTime = time + 1.;
        }

        void drawParticles() {
            
            float angle = 2. * M_PI / (float)(numParticles - 1);
            float ang = 0.;

            for (int i = 0; i < numParticles; i++) {
                glPushMatrix();
                    glColor3f(color[0], color[1], color[2]);
                    glTranslatef(radius * cos(ang) + originX, radius * sin(ang) +  originY, originZ);
                    glCallList(particleList);
                    ang += angle;
                glPopMatrix();
            }
            // if (time < endTime) {

            // }
        }

    private:
        int numParticles;
        float originX, originY, originZ;
        float originTime, endTime, radius;
        float *color;

        GLuint particleList;
};