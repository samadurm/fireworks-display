#pragma once
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"


float *Array3( float a, float b, float c );
float *MulArray3( float factor, float array0[3] );
void SetPointLight( int ilight, float x, float y, float z,  float r, float g, float b );
void SetSpotLight( int ilight, float x, float y, float z,  float xdir, float ydir, float zdir, float r, float g, float b );
void SetMaterial( float r, float g, float b,  float shininess );
