#include "Render.h"
#include "VectorMath.h"

void WritePixel24Bpp(uchar *Buf,
ushort LenghtX,ushort X,ushort Y,
uchar R,uchar G,uchar B)
{
	uchar *Pixel = &Buf[LenghtX*Y*3+X*3];
	Pixel[0] = B;
	Pixel[1] = G;
	Pixel[2] = R;
}

ushort ToScreen(float Cord,ushort ScreenMax)
{
	ushort Half = ScreenMax/2;
	return (ushort)Half+(Cord*Half);
}

//NDC
float ToSpace(ushort Cord,ushort MaxCord)
{
	float Out = (float)(2.0*Cord/MaxCord) - 1.0; 
	return Out;
}

void ProjectVertex(RenderContext *RC,Point3D *Verts,
ushort NumOfVerts,Point3D *OutProject)
{
	float CPDz = RC->CameraPoint.Z - RC->PlanePoint.Z;
	//Camera-Plane Distance in z axis
	for(ushort i = 0;i < NumOfVerts;i++)
	{
		OutProject[i].Z = Verts[i].Z;
		float Zdist = RC->CameraPoint.Z-Verts[i].Z;
		
		OutProject[i].X = (Verts[i].X*CPDz)/Zdist;
		OutProject[i].Y = (Verts[i].Y*CPDz)/Zdist;
	} 
}

void TranslateVertex(Point3D *Vert,Point3D *TV,ushort NumOfVerts)
{
	for(ushort i = 0; i < NumOfVerts;i++)
	{
		Vert[i].X += TV->X;
		Vert[i].Y += TV->Y;
		Vert[i].Z += TV->Z;
	}
}

void RotateVertexFixZ(Point3D *Vert,float Rad,ushort NumOfVerts)
{
	for(ushort i = 0;i < NumOfVerts;i++)
	{
		float OldX = Vert[i].X;
		float OldY = Vert[i].Y;
		Vert[i].X = OldX*cos(Rad) - OldY*sin(Rad);
		Vert[i].Y = OldX*sin(Rad) + OldY*cos(Rad);
	}
}

void RotateVertexFixY(Point3D *Vert,float Rad,ushort NumOfVerts)
{
	for(ushort i = 0;i < NumOfVerts;i++)
	{
		float OldX = Vert[i].X;
		float OldZ = Vert[i].Z;
		Vert[i].X = OldX*cos(Rad) + OldZ*sin(Rad);
		Vert[i].Z = -OldX*sin(Rad) + OldZ*cos(Rad);
	}
}

void RotateVertexFixX(Point3D *Vert,float Rad,ushort NumOfVerts)
{
	for(ushort i = 0;i < NumOfVerts;i++)
	{
		float OldY = Vert[i].Y;
		float OldZ = Vert[i].Z;
		Vert[i].Y = OldY*cos(Rad) - OldZ*sin(Rad);
		Vert[i].Z = OldY*sin(Rad) + OldZ*cos(Rad);
		printf("%f %f %f\n",Vert[i].X,Vert[i].Y,Vert[i].Z);
	}
	
	
}


void DrawTriangles(Point3D *Verts,ushort *List,ushort NumOfTris,
ushort X,ushort Y,uchar *Buf)
{
	for(ushort i = 0;i < NumOfTris*3;i+=3)
	{
		Point3D *TriVerts[3];
		for(uchar i2 = 0; i2 < 3;i2++)
		{
			TriVerts[i2] = &Verts[List[i+i2]];
		}
		Point3D *A = TriVerts[0];
		Point3D *B = TriVerts[1];
		Point3D *C = TriVerts[2];
		
		Point3D AB;
		Point3D BC;
		Point3D CA;
		
		SubPoint3D(A,B,&AB);
		SubPoint3D(B,C,&BC);
		SubPoint3D(C,A,&CA);
		
		float Xmin;
		float Xmax;
		
		float Ymin;
		float Ymax;
		
		float Zmin;
		float Zmax;
		
		FindMaxMinComponent3dPA(
		TriVerts,3,
		&Xmin,&Ymin,&Zmin,
		&Xmax,&Ymax,&Zmax);
				
		for(ushort wY = ToScreen(Ymin,Y);
		wY < ToScreen(Ymax,Y);wY++)
		{
			for(ushort wX = ToScreen(Xmin,X);
			wX < ToScreen(Xmax,X);wX++)
			{	
				Point3D P;
				P.X = ToSpace(wX,X);
				P.Y = ToSpace(wY,Y);
				
				P.Z = 0;
				
				Point3D AP;
				Point3D BP;
				Point3D CP;
				SubPoint3D(A,&P,&AP);
				SubPoint3D(B,&P,&BP);
				SubPoint3D(C,&P,&CP);
				
				float Rez[4];
				Rez[3] = 0;
				Rez[0] = Cross2d3d(&AB,&AP); 
				Rez[1] = Cross2d3d(&BC,&BP);
				Rez[2] = Cross2d3d(&CA,&CP);
				
				if(Rez[0] > 0 && Rez[1] > 0 && Rez[2] > 0)
				{
					Rez[3] = 1;
				}
				if(Rez[0] < 0 && Rez[1] < 0 && Rez[2] < 0)
				{
					Rez[3] = 1;
				}
				if(Rez[3] == 1)
				{
					if(wX < X && wY < Y)
					{
						WritePixel24Bpp(Buf,X,wX,wY,0xFF,0,0);
					}
				}	
			} 
		}
	}
}

