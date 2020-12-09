#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

class Explosion {
    public:
        Explosion(int numParticles) 
            : numParticles(numParticles) {
            color = new float[3];
            duration = 1000.; // 1000ms = 1 second
            radius = 0.2;
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
        }

        void setOriginTime(float time) {
            originTime = time;
            endTime = time + duration;
            printf("origin time %f and endtime is %f\n", originTime, endTime);
        }

        void updateParticles(float time) {
            // printf("time is %f, originTime is %f, endtime is %f\n", time, originTime, endTime);
            if (time < endTime) {
                radius += ((time - originTime) / 1000.) / 1000.;
            }
        }

        void drawParticles() {
            
            float angle = 2. * M_PI / (float)(numParticles - 1);
            float ang = 0.;
            float mid = 0.2;

            glPushMatrix();
                glColor3f(color[0], color[1], color[2]);
                glTranslatef(originX, originY+mid, originZ);
                glCallList(particleList);
            glPopMatrix();

            const float g = 9.8 / 1000;

            for (int i = 0; i < numParticles; i++) {
                glPushMatrix();
                    glTranslatef(radius * cos(ang) + originX, radius * sin(ang) + originY, originZ);
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
        float originTime, endTime, duration, radius;
        float *color;

        GLuint particleList;
};