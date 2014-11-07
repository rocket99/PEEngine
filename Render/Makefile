#Makefile

CC=g++ --std=c++11

D_link = -DGL_GLEXT_PROTOTYPES

ALL:PEShaders.o PEShaderManager.o PEGLProgram.o 

PEShaders.o:PEShaders.cpp PEShaders.h
	$(CC) -c PEShaders.cpp
PEGLProgram.o:PEGLProgram.cpp PEGLProgram.h
	$(CC) -c PEGLProgram.cpp  $(D_link)
PEShaderManager.o:PEShaderManager.cpp PEShaderManager.h
	$(CC) -c PEShaderManager.cpp  $(D_link)

clean:
	rm *.o

