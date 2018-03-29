#include "Defines.h"
#include "VectorMath.h"

typedef struct
{
	Point3D CameraPoint;
	Point3D PlanePoint; 
}RenderContext;

void ProjectVertex(RenderContext *RC,Point3D *Verts,
ushort NumOfVerts,Point3D *OutProject);

void TranslateVertex(Point3D *Vert,Point3D *TV,ushort NumOfVerts);
void RotateVertexFixZ(Point3D *Vert,float Rad,ushort NumOfVerts);
void RotateVertexFixY(Point3D *Vert,float Rad,ushort NumOfVerts);
void RotateVertexFixX(Point3D *Vert,float Rad,ushort NumOfVerts);

void DrawTriangles(Point3D *Verts,ushort *List,ushort NumOfTris,
ushort X,ushort Y,uchar *Buf);
