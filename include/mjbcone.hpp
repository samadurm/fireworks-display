#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

struct point {
	float x, y, z;		// coordinates
	float nx, ny, nz;	// surface normal
	float s, t;		// texture coords
};

inline void DrawPointCone( struct point *p );
inline struct point *PtsPointerCone( struct point *pts, int numLngs, int numLats, int lat, int lng );
void MjbCone( float radBot, float radTop, float height, int slices, int stacks );
float Dot( float v1[3], float v2[3] );
void Cross( float v1[3], float v2[3], float vout[3] );
float Unit( float v[3] );
float Unit( float vin[3], float vout[3] );

