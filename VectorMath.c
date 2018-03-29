#include "VectorMath.h"

float Dot3d(Point3D *V1,Point3D *V2)
{
	return (V1->X*V2->X + V1->Y*V2->Y + V1->Z*V2->Z);
}

float Dot2d3d(Point3D *V1,Point3D *V2)
{
	return (V1->X*V2->X + V1->Y*V2->Y);	
}

void Cross3d(Point3D *V1,Point3D *V2,Point3D *Out)
{
	Out->X = V1->Y*V2->Z - V1->Z*V2->Y;
	Out->Y = V1->Z*V2->X - V1->X*V2->Z;
	Out->Z = V1->X*V2->Y - V1->Y*V2->X;
}

float Cross2d3d(Point3D *V1,Point3D *V2)
{
	return V1->X*V2->Y - V1->Y*V2->X;
}

void SubPoint3D(Point3D *V1,Point3D *V2,Point3D *Out)
{
	Out->X = V1->X-V2->X;
	Out->Y = V1->Y-V2->Y;
	Out->Z = V1->Z-V2->Z;
}

float EdgeFunction(Point3D *V1,Point3D *V2,Point3D *V3)
{
	return (V3->X - V1->X)*(V2->Y - V1->Y) -
	(V3->Y - V1->Y)*(V2->X-V1->X);
}

void FindMaxMinComponent3dPA(Point3D **Vectors,
ushort NumOfVectors,
float *OutXMin,float *OutYMin,
float *OutZMin,float *OutXMax,
float *OutYMax,float *OutZMax)

{
	float MinX = Vectors[0]->X;
	float MaxX = Vectors[0]->X;
	
	float MinY = Vectors[0]->Y;
	float MaxY = Vectors[0]->Y;
	
	float MinZ = Vectors[0]->Z;
	float MaxZ = Vectors[0]->Z;
	
	for(ushort i = 0;i < NumOfVectors;i++)
	{
		if(Vectors[i]->X < MinX)
		{
			MinX = Vectors[i]->X;
		}
		if(Vectors[i]->Y < MinY)
		{
			MinY = Vectors[i]->Y;
		}
		if(Vectors[i]->Z < MinZ)
		{
			MinZ = Vectors[i]->Z;
		}
		
		if(Vectors[i]->X > MaxX)
		{
			MaxX = Vectors[i]->X;
		}
		if(Vectors[i]->Y > MaxY)
		{
			MaxY = Vectors[i]->Y;
		}
		if(Vectors[i]->Z > MaxZ)
		{
			MaxZ = Vectors[i]->Z;
		}
	}
	*OutXMin = MinX;
	*OutYMin = MinY;
	*OutZMin = MinZ;
	
	*OutXMax = MaxX;
	*OutYMax = MaxY;
	*OutZMax = MaxZ;
}
