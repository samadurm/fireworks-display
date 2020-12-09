#include "mjbcone.hpp"

inline void
DrawPointCone( struct point *p )
{
	glNormal3f( p->nx, p->ny, p->nz );
	glTexCoord2f( p->s, p->t );
	glVertex3f( p->x, p->y, p->z );
}

inline struct point *
PtsPointerCone( struct point *pts, int numLngs, int numLats, int lat, int lng )
{
	if( lat < 0 )	lat += (numLats-1);
	if( lng < 0 )	lng += (numLngs-1);
	if( lat > numLats-1 )	lat -= (numLats-1);
	if( lng > numLngs-1 )	lng -= (numLngs-1);
	return &pts[ numLngs*lat + lng ];
}

void
MjbCone( float radBot, float radTop, float height, int slices, int stacks )
{
	// gracefully handle degenerate case:

	if( radBot == 0.  &&  radTop == 0. )
	{
		glBegin( GL_LINES );
			glNormal3f( 0., -1., 0. );
			glTexCoord2f( 0., 0. );
			glVertex3f( 0., 0., 0. );

			glNormal3f( 0., 1., 0. );
			glTexCoord2f( 0., 1. );
			glVertex3f( 0., height, 0. );
		glEnd( );
		return;
	}


	radBot = fabs( radBot );
	radTop = fabs( radTop );
	slices = abs( slices );
	stacks = abs( stacks );
	//fprintf( stderr, "%8.3f, %8.3f, %8.3f,  %3d, %3d\n", radBot, radTop, height, slices, stacks );

	int numLngs = slices;
	if( numLngs < 3 )
		numLngs = 3;

	int numLats = stacks;
	if( numLats < 3 )
		numLats = 3;

	// allocate the point data structure:

	struct point *pts = new struct point[ numLngs * numLats ];

	// fill the pts structure:

	for( int ilat = 0; ilat < numLats; ilat++ )
	{
		float t = (float)ilat / (float)(numLats-1);
		float y = t * height;
		float rad = t * radTop + ( 1. - t ) * radBot;
		for( int ilng = 0; ilng < numLngs; ilng++ )
		{
			float lng = -M_PI  +  2. * M_PI * (float)ilng / (float)(numLngs-1);
			float x =  cos( lng );
			float z = -sin( lng );
			struct point *p = PtsPointerCone( pts, numLngs, numLats, ilat, ilng );
			p->x  = rad * x;
			p->y  = y;
			p->z  = rad * z;
			p->nx = height*x;
			p->ny = radBot - radTop;
			p->nz = height*z;
			Unit( &p->nx );
			p->s = (float)ilng / (float)(numLngs-1);
			p->t = (float)ilat / (float)(numLats-1);
		}
	}


	// draw the sides:

	for( int ilat = 0; ilat < numLats-1; ilat++ )
	{
		glBegin( GL_TRIANGLE_STRIP );

		struct point *p;
		p = PtsPointerCone( pts, numLngs, numLats, ilat,   0 );
		DrawPointCone( p );

		p = PtsPointerCone( pts, numLngs, numLats, ilat+1, 0 );
		DrawPointCone( p );

		for( int ilng = 1; ilng < numLngs; ilng++ )
		{
			p = PtsPointerCone( pts, numLngs, numLats, ilat,   ilng );
			DrawPointCone( p );

			p = PtsPointerCone( pts, numLngs, numLats, ilat+1, ilng );
			DrawPointCone( p );
		}

		glEnd( );
	}

	// draw the bottom circle:

	if( radBot != 0. )
	{
		struct point *bot = new struct point [numLngs];
		for( int ilng = 0; ilng < numLngs; ilng++ )
		{
			bot[ilng].x  = 0.;
			bot[ilng].y  = 0.;
			bot[ilng].z  = 0.;
			bot[ilng].nx =  0.;
			bot[ilng].ny = -1.;
			bot[ilng].nz =  0.;
			bot[ilng].s = (float)ilng / (float)(numLngs-1);
			bot[ilng].t = 0.;
		}

		glBegin( GL_TRIANGLES );
		for( int ilng = numLngs-1; ilng >= 0; ilng-- )
		{
			struct point *p;
			p = PtsPointerCone( pts, numLngs, numLats, 0, ilng+1 );
			DrawPointCone( p );

			p = PtsPointerCone( pts, numLngs, numLats, 0, ilng );
			DrawPointCone( p );

			DrawPointCone( &bot[ilng] );
		}
		glEnd( );
		delete[ ] bot;
	}


	// draw the top circle:

	if( radTop != 0. )
	{
		struct point *top = new struct point [numLngs];
		for( int ilng = 0; ilng < numLngs; ilng++ )
		{
			top[ilng].x  = 0.;
			top[ilng].y  = height;
			top[ilng].z  = 0.;
			top[ilng].nx = 0.;
			top[ilng].ny = 1.;
			top[ilng].nz = 0.;
			top[ilng].s = (float)ilng / (float)(numLngs-1);
			top[ilng].t = 1.;
		}

		glBegin( GL_TRIANGLES );
		for( int ilng = 0; ilng < numLngs-1; ilng++ )
		{
			struct point *p;
			p = PtsPointerCone( pts, numLngs, numLats, numLats-1, ilng );
			DrawPointCone( p );

			p = PtsPointerCone( pts, numLngs, numLats, numLats-1, ilng+1 );
			DrawPointCone( p );

			DrawPointCone( &top[ilng] );
		}
		glEnd( );
		delete [ ] top;
	}

	delete [ ] pts;
}

float
Dot( float v1[3], float v2[3] )
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void
Cross( float v1[3], float v2[3], float vout[3] )
{
	float tmp[3];

	tmp[0] = v1[1]*v2[2] - v2[1]*v1[2];
	tmp[1] = v2[0]*v1[2] - v1[0]*v2[2];
	tmp[2] = v1[0]*v2[1] - v2[0]*v1[1];

	vout[0] = tmp[0];
	vout[1] = tmp[1];
	vout[2] = tmp[2];
}

float
Unit( float v[3] )
{
	float dist;

	dist = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];

	if( dist > 0.0 )
	{
		dist = sqrt( dist );
		v[0] /= dist;
		v[1] /= dist;
		v[2] /= dist;
	}

	return dist;
}

float
Unit( float vin[3], float vout[3] )
{
	float dist;

	dist = vin[0]*vin[0] + vin[1]*vin[1] + vin[2]*vin[2];

	if( dist > 0.0 )
	{
		dist = sqrt( dist );
		vout[0] = vin[0] / dist;
		vout[1] = vin[1] / dist;
		vout[2] = vin[2] / dist;
	}
	else
	{
		vout[0] = vin[0];
		vout[1] = vin[1];
		vout[2] = vin[2];
	}

	return dist;
}
