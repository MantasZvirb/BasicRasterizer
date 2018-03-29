#include <stdio.h>
#include "Defines.h"

typedef struct HEADER
{
   char  idlength;
   char  colourmaptype;
   char  datatypecode;
   short int colourmaporigin;
   short int colourmaplength;
   char  colourmapdepth;
   short int x_origin;
   short int y_origin;
   short width;
   short height;
   char  bitsperpixel;
   char  imagedescriptor;
}__attribute__((packed)) HEADER;

void WriteTGA(char *FilePath,uchar *Pixels,ushort X,ushort Y)
{
	HEADER Hdr;
	Hdr.idlength = 0;
	Hdr.colourmaptype = 2;
	Hdr.datatypecode = 2;
	Hdr.colourmaporigin = 0;
	Hdr.colourmaplength = 0;
	Hdr.x_origin = 0;
	Hdr.y_origin = 0;
	Hdr.width = X;
	Hdr.height = Y;
	Hdr.bitsperpixel = 24;
	Hdr.imagedescriptor = 0;
	
	FILE *Fd = fopen(FilePath,"wb");
	fwrite(&Hdr,1,sizeof(HEADER),Fd);
	fwrite(Pixels,1,X*Y*3,Fd);
	fclose(Fd);
} 
