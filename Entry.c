#include <stdio.h>
#include <math.h>

#include "Defines.h"
#include "Tga.h"
#include "Render.h"

int main(ulong argc,uchar *argv[])
{
	int X = 640;
	int Y = 480;
	uchar *Buf = malloc(X*Y*3);

	RenderContext RC = {0};
	RC.CameraPoint.Z = -5;
	RC.PlanePoint.Z = -4;

	Point3D Verts[3];
	Point3D ProjVerts[3];
	ushort List[3];
	List[0] = 0;
	List[1] = 1;
	List[2] = 2;

	Verts[0].X = -0.5;
	Verts[0].Y = 0;
	Verts[0].Z = 2;

	Verts[1].X = 0;
	Verts[1].Y = 0.5;
	Verts[1].Z = 2;

	Verts[2].X = 0.5;
	Verts[2].Y = 0;
	Verts[2].Z = 2;
	
	Point3D Vrt[3];
	Vrt[0].X = -1;
	Vrt[0].Y = 0;
	Vrt[0].Z = 3;
	
	Vrt[1].X = -0.5;
	Vrt[1].Y = 1;
	Vrt[1].Z = 3;
	
	Vrt[2].X = 0;
	Vrt[2].Y = 0;
	Vrt[2].Z = 3;
	Point3D PV2[3];
	
	
	Point3D TV;
	TV.X = -1.5;
	TV.Y = 0;
	TV.Z = 0;
	
	TranslateVertex(Vrt,&TV,3);
	
	//TranslateVertex(Verts,&TV,3);
	RotateVertexFixY(Verts,M_PI*1.5,3);
	ProjectVertex(&RC,Verts,3,ProjVerts);
	ProjectVertex(&RC,Vrt,3,PV2);
	DrawTriangles(ProjVerts,List,1,X,Y,Buf);
	//DrawTriangles(PV2,List,1,X,Y,Buf);
	WriteTGA("./Test.tga",Buf,X,Y);

	return 0;
}
