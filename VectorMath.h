#include "Defines.h"
#include <math.h>
#ifndef VECTORMATH_H
#define VECTORMATH_H

typedef struct 
{
	float X,Y,Z;
}Point3D;

typedef struct 
{
	float X,Y;
}Point2D;

typedef struct 
{
	Point2D A,B,C;
}Triangle2D;

typedef struct 
{
	Point3D A,B,C;
}Traingle3D;


float Dot3d(Point3D *V1,Point3D *V2);
float Dot2d3d(Point3D *V1,Point3D *V2);
void Cross3d(Point3D *V1,Point3D *V2,Point3D *Out);
float Cross2d3d(Point3D *V1,Point3D *V2);
void SubPoint3D(Point3D *V1,Point3D *V2,Point3D *Out);
float EdgeFunction(Point3D *V1,Point3D *V2,Point3D *V3);

void FindMaxMinComponent3dPA(Point3D **Vectors,ushort NumOfVectors,
float *OutXMin,float *OutYMin,float *OutZMin,float *OutXMax,
float *OutYMax,float *OutZMax);

#endif
