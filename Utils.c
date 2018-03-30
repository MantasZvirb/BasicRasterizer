#include "Utils.h"
#include <stdio.h>

char FileWrite(uchar *Path,uchar *Data,ulong Size)
{
	FILE *Fd = fopen(Path,"wb");
	if(Fd == 0)
	{
		return -1;
	}
	ulong Sz = fwrite(Data,1,Size,Fd);
	char RetVal = 1;
	if(Sz != Size)
	{
		RetVal = -2;
	}
	fclose(Fd);
	return RetVal;
}

char FileRead(uchar *Path,ulong *OutSize,uchar **OutData)
{
	FILE *Fd = fopen(Path,"rb");
	if(Fd == 0)
	{
		return -1;
	}
	ulong Fs;
	ulong SeekRt = fseek(Fd,0,SEEK_END);
	Fs = ftell(Fd);
	if(Fs == -1 || SeekRt == -1)
	{
		return -2;
	}
	rewind(Fd);
	
	*OutData = malloc(Fs);
	if(OutSize != 0)
	{
		*OutSize = Fs;
	}
	ulong SzRt = fread(*OutData,1,Fs,Fd);
	char RtVal = 1;
	if(SzRt != Fs)
	{
		free(*OutData);
		RtVal = -3;
	}
	fclose(Fd);
	return RtVal;
}
