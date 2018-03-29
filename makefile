Files = Entry.c Render.c Render.h Tga.c Tga.h Defines.h VectorMath.c VectorMath.h Utils.c Utils.h
Lib = -lm
Flags = -s -O3

Command = $(Files) $(Lib) $(Falgs)

all:
	gcc $(Command)
